#ifndef H_ZOOM
#define H_ZOOM

#ifdef USE_ZOOM
SDL_Surface *zoomSurface(SDL_Surface * src, double zoomx, double zoomy, int smooth);
#endif
void scale2x( SDL_Surface *src, SDL_Surface *dst );

#endif // H_ZOOM
