// 8080EmulatorVS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <SDL.h>
#undef main

using namespace std;

int PrintAssembly(unsigned char*, int);

int main(int argc, char** argv)
{
	// Open ROM file
	FILE *f;
	int errorcode = fopen_s(&f, argv[1], "rb");
	if (errorcode != 0)
	{
		printf("Error: Could not open file %s\n", argv[1]);
		exit(1);
	}

	fseek(f, 0L, SEEK_END);
	int fsize = ftell(f);
	fseek(f, 0L, SEEK_SET);

	// Allocate space in memory for the ROM
	unsigned char *buffer = (unsigned char*)malloc(fsize);

	fread(buffer, fsize, 1, f);
	fclose(f);

	// Print ROM assembly instructions
	int pc = 0;
	while (pc < fsize)
	{
		pc += PrintAssembly(buffer, pc);
	}

	return 0;
}

int PrintAssembly(unsigned char* codebuffer, int pc)
{
	unsigned char *code = &codebuffer[pc];
	int opbytes = 1;
	printf("%04x ", pc);
	switch (*code)
	{
	case 0x00: printf("NOP"); break;
	case 0x01: printf("LXI B,#$%02x%02x", code[2], code[1]); opbytes = 3; break;
	case 0x02: printf("STAX B"); break;
	case 0x03: printf("INX B"); break;
	case 0x04: printf("INR B"); break;
	case 0x05: printf("DCR B"); break;
	case 0x06: printf("MVI B,#$%02x", code[1]); opbytes = 2; break;
	case 0x07: printf("RLC"); break;
	case 0x08: printf("NOP"); break;
	case 0x3e: printf("MVI A,#0x%02x", code[1]); opbytes = 2; break;
	case 0xc3: printf("JMP $%02x%02x", code[2], code[1]); opbytes = 3; break;
	default: printf("Instruction not implemented.");
	}

	printf("\n");

	return opbytes;
}

/*

void PutPixel32_nolock(SDL_Surface*, int, int, Uint32);

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		return 1;
	}
	
	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr)
	{
		SDL_DestroyWindow(win);
		cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
		SDL_Quit();
		return 1;
	}

	SDL_Surface *surface = SDL_CreateRGBSurface(0, 640, 480, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
	if (surface == nullptr)
	{
		SDL_DestroyWindow(win);
		cout << "Error: " << SDL_GetError() << endl;
		SDL_Quit();
		return 1;
	}

	for (int i = 0; i < 640; i++)
	{
		for (int j = 0; j < 480; j++)
		{
			PutPixel32_nolock(surface, i, j, 0x00000000);
		}		
	}
	

    return 0;
}

void PutPixel32_nolock(SDL_Surface * surface, int x, int y, Uint32 color)
{
	Uint8 * pixel = (Uint8*)surface->pixels;
	pixel += (y * surface->pitch) + (x * sizeof(Uint32));
	*((Uint32*)pixel) = color;
}

*/