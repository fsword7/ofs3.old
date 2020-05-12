/*
 * texture.h - texture package for OpenGL
 *
 *  Created on: May 12, 2020
 *      Author: Tim Stark
 */

#pragma once

class Texture
{
public:
	enum MipMapMode {
		NoMipMaps    = 0,
		FixedMipMaps = 1,
		AutoMipMaps  = 2
	};

	enum BorderMode {
		Wrap        = 0,
		BorderClamp = 1,
		EdgeClamp   = 2
	};

	Texture(uint32_t width, uint32_t height);
	~Texture();

    inline bool isCompressed() const { return compressed; }
    inline bool isLoaded() const     { return loadFlag; }
    inline void bind() const         { glBindTexture(GL_TEXTURE_2D, name); }
    inline void unbind() const       { glBindTexture(GL_TEXTURE_2D, 0); }

    // void bind();
    void load();

    int getFormatComponents(int format);
    int getDataSize(int w, int h, int format);

    static Texture *loadDDSFromMemory(uint8_t *data, uint32_t size);
    static Texture *loadDDSFromFile(const string &fname);
    static Texture *create(const string &fname);

    inline int pad(int n) const { return (n + 3) & ~0x3; };

private:
	uint32_t width, height;
	uint32_t size;

    int      format;
    bool     compressed;

    uint32_t components = 0;

	uint8_t *data = nullptr;

	MipMapMode mipMode    = NoMipMaps;
	BorderMode borderMode = EdgeClamp;

	bool loadFlag = false;
	GLuint name = 0;
};
