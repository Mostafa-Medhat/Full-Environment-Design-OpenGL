# Assignment 3 :Computer Graphics Full Environment Design.

- the main idea of this assignment was to understand how to make full invironment using opengl.

- First of all we started by creating a 3D shape and understand the main operations that can be done to it like(translation , rotation , scaling) and trying to compine all of these to make our robotic body.

- Then we tried to understand stacks very well as it's very important in opengl, and know when to push matrix and when to pop it inorder to have the result we wanted .

- As opengl uses stacks so the operation are operated by the (LIFO) or last in first out so in order to creat a cube and give its scal and transfer it we used the same methods used in the previous assignments.  

- after drawing the full body and apply it's movments as the previous assignments we added the floor and assign it's texture then we put the robot's body on top of this floor.

-in order to make the scene more realistic we made full room and assign deffrent textures to the walls than the floor. 

-we made also some movements that the robot can do and some that interact with the objects in the scene.

-we added a menu to choose from it which movement we want and also which floor texture we want.

- we used several functions as:

```
GLuint loadTexture(Image* image)
{
	GLuint textureId;
	glGenTextures(1, &textureId);			 //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,				  //Always GL_TEXTURE_2D
		0,							  //0 for now
		GL_RGB,					  //Format OpenGL uses for image
		image->width, image->height, //Width and height
		0,							  //The border of the image
		GL_RGB,					  //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE,			  //GL_UNSIGNED_BYTE, because pixels are stored
									 //as unsigned numbers
		image->pixels);			  //The actual pixel data
	return textureId;						  //Returns the id of the texture
}
```
```
GLuint _textureId; //The id of the texture
GLuint _textureId2;
//Initializes 3D rendering
```
```
void initRendering()
{
	Image* image = loadBMP(floorTexture);
	_textureId = loadTexture(image);
    Image* image2 = loadBMP("images/wall.bmp");
    _textureId2 = loadTexture(image2);
	delete image;
    delete image2;
	// Turn on the power
	glEnable(GL_LIGHTING);
	// Flip light switch
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
	// assign light parameters
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
	// Material Properties
	GLfloat lightColor1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor1);
	glEnable(GL_NORMALIZE);
	//Enable smooth shading
	glShadeModel(GL_SMOOTH);
	// Enable Depth buffer
	glEnable(GL_DEPTH_TEST);
}
```
this functions are used to take any photo we want and make it into texture that we can use to put on top of the floor and walls.

-we used also:
```
void drawmodel(char* filename)
{
    GLMmodel* model = glmReadOBJ(filename);
    glmUnitize(model);
    glmFacetNormals(model);
    glmVertexNormals(model, 90.0);
    glmScale(model, .15);
    glmDraw(model, GLM_SMOOTH | GLM_MATERIAL);
}
```

this function is used to take .obj file and draw it into the scene.

# Result Sample:
## Static Scene:
<p align="center">
  <img src="https://drive.google.com/uc?export=view&id=14Glib58MeK0rV8_LekFu6BV20j3rPVnC">
</p>

## Animated Scenes:
### Without Object Interaction:
#### Animation 1 (Push Up) :
<p align="center">
  <img src="https://github.com/sbme-tutorials/task3-biomedical_graphics/blob/main/task3/Gifs/Task3%20CG%20-%20Push%20Up.gif?raw=true">
</p>

#### Animation 2 (Front Flip) :
<p align="center">
  <img src="https://github.com/sbme-tutorials/task3-biomedical_graphics/blob/main/task3/Gifs/Task3%20CG%20-%20Flip.gif?raw=true">
</p>

### With Object Interaction:
#### Animation 3 (Bicycle Kick):
<p align="center">
  <img src="https://github.com/sbme-tutorials/task3-biomedical_graphics/blob/main/task3/Gifs/Task3%20CG-Ball.gif?raw=true">
</p>

# Issues we faced:

- the main issue we faced was to understand how to assign textures and how to draw models in the scene.

- we also faced some dificulty tring to find .obj files that work well in our code.

- to make the movments it took some effort to get the positions and to make functions that take it and show it using timer function
