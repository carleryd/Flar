#include "scrolltemp.h"


#ifndef _MAP_H
#define _MAP_H

/*
 Map data files have the following format:
 <string filename>
 <int number of tiles across the tilesheet>
 <int cell width>
 <int cell height>
 <int map width>
 <int map height>
 <int map data, formatted as rows and columns seperated by spaces and newlines>
 */
#include <SFML/graphics.hpp>
#include <vector>
#include <string>
#include <fstream>

using namespace std;


class Map
{
private:
	int rows, cols; //the # of rows and columns in the map array
	sf::RenderWindow *App;
	
	sf::RenderImage *buffer; //the off-screen scroll buffer
	
	//int target_x, target_y; //where, in world coordinates, we want to center the screen on
	float scroll_offset_x, scroll_offset_y;                 //where we have scrolled to in the world, upper-left corner in pixels
	int buffer_scroll_offset_x, buffer_scroll_offset_y;     //where we have scrolled to in the buffer, upper-left corner in pixels
	int buffer_index_x, buffer_index_y;                     //where, in map indices, the row and cols of the offscreen buffer start
	int buffer_rows, buffer_cols;                           //how big the buffer is
	sf::Sprite *buffer_sprite;                              //the sprite we use to copy from off-screen to screen
	sf::Sprite *buffer2buffer_sprite;                       //the sprite we use to copy from off-screen to off-screen
	
	sf::Image *tilepic;
	sf::Sprite *tilesheet;
	float origin_x, origin_y; // pixel offsets of where to start drawing the map on the screen
	int num_tiles_across_screen; //how many tiles to display across
	int num_tiles_down_screen; //how many tiles to display down
	vector<vector<int>> *map; //our 2D map array
	int cell_width, cell_height; //dimensions of a single tile, in pixels
	int num_tiles_across_tilesheet;//how many tiles are in a row on the tilesheet
    
	void FillBuffer(int index_x, int index_y);
public:
	void Scroll(float delta_x, float delta_y);
	void SetScreen(float x, float y, int tiles_across, int tiles_down); //call before LoadMap
	bool LoadMap(string fname);
	bool SaveMap(string fname);
	void DrawTile(int tile_num, int x, int y);
	void DrawMap(void);
	void FreeMem(void);
	Map(sf::RenderWindow *the_App);
	~Map(void);
};


void Map::Scroll(float delta_x, float delta_y)
{
	//store the old scroll offsets, so we can compare after bounds-checking
	int offset_x = (int)scroll_offset_x;
	int offset_y = (int)scroll_offset_y;
    
	scroll_offset_x += delta_x;
	scroll_offset_y += delta_y;
    
	//bounds check
	if(scroll_offset_x < 0.f) scroll_offset_x = 0.f;
	if(scroll_offset_y < 0.f) scroll_offset_y = 0.f;
	
	if(scroll_offset_x > ((cols * cell_width) - (num_tiles_across_screen * cell_width)) )
	{
		scroll_offset_x = (float)((cols * cell_width) - (num_tiles_across_screen * cell_width));
	}
    
	if(scroll_offset_y > ((rows * cell_height) - (num_tiles_down_screen * cell_height)) )
	{
		scroll_offset_y = (float)((rows * cell_height) - (num_tiles_down_screen * cell_height));
	}
    
	//our world scroll coords are now updated, so go on to adjust our off-screen buffer
	//first, calculate how much we actually scrolled by
	offset_x =  (int)scroll_offset_x - offset_x;
	offset_y =  (int)scroll_offset_y - offset_y;
	
	//instead of recaculculating the buffer scroll offsets like this:
	//buffer_scroll_offset_x = scroll_offset_x - (buffer_index_x * cell_width);
	//buffer_scroll_offset_y = scroll_offset_y - (buffer_index_y * cell_height);
	//...we can just add the integer offsets we previously calculated:
	buffer_scroll_offset_y += offset_y;
	buffer_scroll_offset_x += offset_x;
	//only bother to try and scroll if we actually moved...may not have been allowed to scroll
	//because of the bounds checks
	//first, do x-axis scrolling
	if(offset_x != 0)
	{
		//we have actually scrolled the map, but may not have blown the cached tile buffer yet.
		//So, we bounds check, to see if we scrolled out of our off-screen buffer
        
		//too far left? update buffer until we are legal
		while(buffer_scroll_offset_x < 0)
		{
			buffer_scroll_offset_x += cell_width;
			buffer_index_x--;
			//copy columns over, shifted right
			sf::IntRect rect2;
			rect2.Top = 0;
			rect2.Width = cell_width;
			rect2.Height = (num_tiles_down_screen + 2) * cell_height;
			for(int i = num_tiles_across_screen ; i >= 0 ; --i)
			{
				rect2.Left = i*cell_width;
				buffer2buffer_sprite->SetSubRect(rect2);
				buffer2buffer_sprite->SetPosition((i+1)*cell_width, 0.f);
				buffer->Draw(*buffer2buffer_sprite);
			}
            
			int yloc;//where the upper left corner of the tile should be drawn
            //to the buffer, in pixels
			//fill in the new tiles we need, to fill the spot we shifted over from
			for(int y = buffer_index_y; y < num_tiles_down_screen + buffer_index_y + 2; ++y)
			{
				yloc = ( (y-buffer_index_y) * cell_height);
                
				DrawTile((*map)[buffer_index_x][y], 0, yloc);
			}
            
			//now that all buffer updating is done, render the image
			buffer->Display();
		}
        
		//too far right? update buffer until we are legal
		while(buffer_scroll_offset_x > (cell_width * 2))
		{
			buffer_scroll_offset_x -= cell_width;
			buffer_index_x++;
			//copy columns over, shifted left
			sf::IntRect rect2;
			rect2.Top = 0;
			rect2.Width = cell_width;
			rect2.Height = (num_tiles_down_screen + 2) * cell_height;
			
			for(int i = 1; i < num_tiles_across_screen + 2; ++i)
			{
				rect2.Left = i * cell_width;
                
				buffer2buffer_sprite->SetSubRect(rect2);
				buffer2buffer_sprite->SetPosition((i-1)*cell_width, 0);
				buffer->Draw(*buffer2buffer_sprite);
			}
            
			int yloc;//where the upper left corner of the tile should be drawn
            //to the buffer, in pixels
			//fill in the new tiles we need, to fill the spot we shifted over from
			for(int y = buffer_index_y; y < num_tiles_down_screen + buffer_index_y + 2; ++y)
			{
				yloc = ( (y-buffer_index_y) * cell_height);
                
				DrawTile((*map)[buffer_index_x+num_tiles_across_screen+1][y], cell_width * (num_tiles_across_screen+1), yloc);
			}
            
			//now that all buffer updating is done, render the image
			buffer->Display();
		}
        
		//we scrolled, so move the buffer sprite  copy area
		sf::IntRect rect;
		rect.Left = buffer_scroll_offset_x;
		rect.Top = buffer_scroll_offset_y;
		rect.Width = num_tiles_across_screen * cell_width;
		rect.Height = num_tiles_down_screen * cell_height;
		buffer_sprite->SetSubRect(rect);
	}
    
	//==========================================
	//secondly, do y-axis scrolling
	if(offset_y != 0)
	{
		//bounds check, see if we scrolled out of our off-screen buffer
        
		//too far up? update buffer until we are legal
		while(buffer_scroll_offset_y < 0)
		{
			buffer_scroll_offset_y += cell_height;
			buffer_index_y--;
			//copy rows over, shifted down
			sf::IntRect rect2;
			rect2.Left = 0;
			rect2.Width = (num_tiles_across_screen + 2) * cell_width;
			rect2.Height = cell_height;
			for(int i = num_tiles_down_screen ; i >= 0 ; --i)
			{
				rect2.Top = i*cell_height;
                
				buffer2buffer_sprite->SetSubRect(rect2);
				buffer2buffer_sprite->SetPosition(0.f, (i+1) * cell_height);
				buffer->Draw(*buffer2buffer_sprite);
			}
            
			int xloc;//where the upper left corner of the tile should be drawn
            //to the buffer, in pixels
			//fill in the new tiles we need, to fill the spot we shifted over from
			for(int x = buffer_index_x; x < num_tiles_across_screen + buffer_index_x + 2; ++x)
			{
				xloc = ( (x-buffer_index_x) * cell_width);
                
				DrawTile((*map)[x][buffer_index_y], xloc, 0);
			}
            
			//now that all buffer updating is done, render the image
			buffer->Display();
		}
        
		//too far down? update buffer until we are legal
		while(buffer_scroll_offset_y > (cell_height * 2))
		{
			buffer_scroll_offset_y -= cell_height;
			buffer_index_y++;
			//copy rows over, shifted left
			sf::IntRect rect2;
			rect2.Left = 0;
			rect2.Width = (num_tiles_across_screen + 2) * cell_width;
			rect2.Height = cell_height;
			for(int i = 1; i < num_tiles_down_screen + 2; ++i)
			{
				rect2.Top = i * cell_height;
                
				buffer2buffer_sprite->SetSubRect(rect2);
				buffer2buffer_sprite->SetPosition(0, (i-1) * cell_height);
				buffer->Draw(*buffer2buffer_sprite);
			}
            
			int xloc;//where the upper left corner of the tile should be drawn
            //to the buffer, in pixels
			//fill in the new tiles we need, to fill the spot we shifted over from
			for(int x = buffer_index_x; x < num_tiles_across_screen + buffer_index_x + 2; ++x)
			{
				xloc = ( (x-buffer_index_x) * cell_width);
                
				DrawTile((*map)[x][buffer_index_y+num_tiles_down_screen+1], xloc, cell_height * (num_tiles_down_screen+1));
			}
            
			//now that all buffer updating is done, render the image
			buffer->Display();
		}
        
		//we scrolled, so move the buffer sprite  copy area
		sf::IntRect rect;
		rect.Left = buffer_scroll_offset_x;
		rect.Top = buffer_scroll_offset_y;
		rect.Width = num_tiles_across_screen * cell_width;
		rect.Height = num_tiles_down_screen * cell_height;
		buffer_sprite->SetSubRect(rect);
	}
}

#endif