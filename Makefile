make:
	g++ -o final final.cpp md2loader/Md2Model.cpp md2loader/Texture.cpp md2loader/Image.cpp BMPLoader/BMPLoader.cpp -lGL -lglut -lGLEW -lGLU
