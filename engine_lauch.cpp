#include "stdlib.h"
#include "stdio.h"
#include "SDL.h"
#include "SDL_syswm.h"
#include "SDL_opengl.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"
//#include "GL/glew.h"
#include <GL/glx.h>
#include <GL/glxext.h>
#include <tinyxml.h>
#include <log_provider_file.h>
#include <log_provider_stdout.h>
#include <gamemanager.h>
cGameManager *cm = NULL;

#define uglGetProcAddress(x) (*glXGetProcAddressARB)((const GLubyte*)(x))
PFNGLCREATEPROGRAMOBJECTARBPROC     glCreateProgramObjectARB = NULL;
PFNGLDELETEOBJECTARBPROC            glDeleteObjectARB = NULL;
PFNGLCREATESHADEROBJECTARBPROC      glCreateShaderObjectARB = NULL;
PFNGLSHADERSOURCEARBPROC            glShaderSourceARB = NULL;
PFNGLCOMPILESHADERARBPROC           glCompileShaderARB = NULL;
PFNGLGETOBJECTPARAMETERIVARBPROC    glGetObjectParameterivARB = NULL;
PFNGLATTACHOBJECTARBPROC            glAttachObjectARB = NULL;
PFNGLGETINFOLOGARBPROC              glGetInfoLogARB = NULL;
PFNGLLINKPROGRAMARBPROC             glLinkProgramARB = NULL;
PFNGLUSEPROGRAMOBJECTARBPROC        glUseProgramObjectARB = NULL;
PFNGLGETUNIFORMLOCATIONARBPROC      glGetUniformLocationARB = NULL;
PFNGLUNIFORM1FARBPROC               glUniform1fARB = NULL;
PFNGLUNIFORM1IARBPROC               glUniform1iARB = NULL;
void setupExtensions()

 
  {
    glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC)
      uglGetProcAddress("glCreateProgramObjectARB");
    glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC)
      uglGetProcAddress("glDeleteObjectARB");
    glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC)
     uglGetProcAddress("glCreateShaderObjectARB");
    glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC)
      uglGetProcAddress("glShaderSourceARB");
    glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC)
      uglGetProcAddress("glCompileShaderARB");
    glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)
      uglGetProcAddress("glGetObjectParameterivARB");
    glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC)
      uglGetProcAddress("glAttachObjectARB");
    glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC)
      uglGetProcAddress("glGetInfoLogARB");
    glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC)
      uglGetProcAddress("glLinkProgramARB");
    glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC)
      uglGetProcAddress("glUseProgramObjectARB");
    glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC)
      uglGetProcAddress("glGetUniformLocationARB");
    glUniform1fARB = (PFNGLUNIFORM1FARBPROC)
      uglGetProcAddress("glUniform1fARB");
    glUniform1iARB = (PFNGLUNIFORM1IARBPROC)
      uglGetProcAddress("glUniform1iARB");

    /*  if( false
     || glActiveTextureARB == NULL
     || glMultiTexCoord2fARB == NULL
     || glCreateProgramObjectARB == NULL
     || glDeleteObjectARB == NULL
     || glCreateShaderObjectARB == NULL
     || glShaderSourceARB == NULL
     || glCompileShaderARB == NULL
     || glGetObjectParameterivARB == NULL
     || glAttachObjectARB == NULL
     || glGetInfoLogARB == NULL
     || glLinkProgramARB == NULL
     || glUseProgramObjectARB == NULL
     || glGetUniformLocationARB == NULL
     || glUniform1fARB == NULL
     || glUniform1iARB == NULL
      )
      //      shading_enabled = false;
    else shading_enabled = true;
  } else
    shading_enabled = false;
    */
}

GLfloat Xrotate;
GLfloat Yrotate;
GLfloat Zrotate;
void DrawCube()
{
static const GLfloat coords[6][4][3] = { 
      { { +1.0, -1.0, +1.0 }, { +1.0, -1.0, -1.0 }, 
        { +1.0, +1.0, -1.0 }, { +1.0, +1.0, +1.0 } }, 
      { { -1.0, -1.0, -1.0 }, { -1.0, -1.0, +1.0 }, 
        { -1.0, +1.0, +1.0 }, { -1.0, +1.0, -1.0 } }, 
      { { +1.0, -1.0, -1.0 }, { -1.0, -1.0, -1.0 }, 
        { -1.0, +1.0, -1.0 }, { +1.0, +1.0, -1.0 } }, 
      { { -1.0, -1.0, +1.0 }, { +1.0, -1.0, +1.0 }, 
        { +1.0, +1.0, +1.0 }, { -1.0, +1.0, +1.0 } }, 
      { { -1.0, -1.0, -1.0 }, { +1.0, -1.0, -1.0 }, 
        { +1.0, -1.0, +1.0 }, { -1.0, -1.0, +1.0 } }, 
      { { -1.0, +1.0, +1.0 }, { +1.0, +1.0, +1.0 }, 
        { +1.0, +1.0, -1.0 }, { -1.0, +1.0, -1.0 } }
};
 
 for (int i=0;i<6;i++)
   for (int j=0;j<4;j++)
     {
       glVertex3f(coords[i][j][0],coords[i][j][1],coords[i][j][2]);
         glColor3d(0,20,0);
     }
}
void DrawScene()
{
  float lpos[4] = {1.0,1,2.5,1.0};
//clear and reset view
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT) ;
//glLoadIdentity();
//show result
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity(); 
   glTranslatef(0, 0, -10.0);
  glRotatef(Xrotate, 1.0, 0.0, 0.0); 
   glRotatef(Yrotate, 0.0, 1.0, 0.0); 
  glRotatef(Zrotate, 0.0, 0.0, -1.0);


glBegin(GL_QUADS);
 DrawCube();
glLightfv(GL_LIGHT0, GL_POSITION, lpos);

glEnd();
SDL_GL_SwapBuffers();
}
void CheckGLSLError(GLhandleARB Handle,GLenum Param)
{
  GLint glsl; 
  char * ch; 
  GLint al;
  al =1; 
glGetObjectParameterivARB(Handle,Param,&glsl);
 ch = (char *)malloc (sizeof(char)*1000);
 glGetInfoLogARB(Handle,1000,&al,ch);
 printf(ch);
 free((void *)ch);
}
char *textFileRead(char *fn) {


	FILE *fp;
	char *content = NULL;

	int f,count;
	fp = fopen(fn, "rb");

	 fseek(fp, 0, SEEK_END);
	 count = ftell(fp);
	printf("sh size  = %d\n",count);
	fclose(fp);

	if (fn != NULL) {
		fp = fopen(fn,"rt");

		if (fp != NULL) {


			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
		else 
		  {
		    printf("read file failed\n");
		  }
	}
	return content;
}


int main(int argc, char **argv)
{
     char *gamefile;
   int result;
     LPENGSTARTDATA  game_config = new cEngStartData;
   TiXmlDocument config("laucher.cfg");
   TiXmlHandle configHandle(&config);
   printf("laucher...\n");
   cm = new cGameManager ;	
    if (!config.LoadFile())
   {
		printf("%s","config.LoadFile - Error on loading config\n");
		exit(-1);
   }
   TiXmlElement* itemElement = 0;

   
   
   itemElement = configHandle.FirstChild("game").FirstChild("config").ToElement();
   gamefile = (char * )itemElement->Attribute("game");

    itemElement->QueryIntAttribute("logging",&result);
    if (result)
	{
		LPLOGPROVIDERSTDOUT lpFProv = new cLogProviderStdout;
		lpFProv->Init();
		
		game_config->lpGameLog = lpFProv;
	}
	else
		game_config->lpGameLog = NULL;
	
       int wndxpos,wndypos,wndxsize,wndysize;
 
   itemElement->QueryIntAttribute("wndxpos",&wndxpos);
   itemElement->QueryIntAttribute("wndypos",&wndypos);
   itemElement->QueryIntAttribute("wndxsize",&wndxsize);
   itemElement->QueryIntAttribute("wndysize",&wndysize);   
   itemElement->QueryIntAttribute("wnddef",&result);
   itemElement->QueryIntAttribute("fullscreen",(int*)&game_config->bFullScreen);
   game_config->xScreenRes = wndxsize;
   game_config->yScreenRes = wndysize;
   itemElement->QueryIntAttribute("sound",(int*)&game_config->bWithSound);
   itemElement->QueryIntAttribute("verboselevel",(int*)&game_config->VerboseLevel);
   itemElement->QueryIntAttribute("maxmessages",(int*)&game_config->MaxMessages);
	game_config->h_BaseWindow = 0;
	game_config->lpGameInitScript = (LPENGSTR)malloc(sizeof(cEng_char)*256);
	strcpy(game_config->lpGameInitScript,(char * )itemElement->Attribute("initsc"));
	//todo: here pointer loose!!!
	cm->Init();
	if (cm->CreateGame(game_config)!= ENG_ERR_SUCCESS)
	{
		printf("%\n","Game create Failed");
		exit(10);
	}

	
	//else
	if (cm->StartGame() != ENG_ERR_SUCCESS)
	{
		printf("%s\n","game start failed");
		exit(10);
	}
  if ( SDL_Init(SDL_INIT_VIDEO) != 0)
    {
      printf("ini SDL error!\n");
      return 1;
    }
   SDL_WM_SetCaption("cube demo |F2-WIRE/FILL|F3-fsh",0);
    SDL_Event event;
    int runing = 1;

    SDL_SetVideoMode(800,600,16,SDL_OPENGL);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,6);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,5);
	glEnable(GL_DEPTH_TEST);
	//	glClearColor(1.0,1.0,1.0,1.0);
    setupExtensions();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = (GLfloat)800 / 600; 
   glViewport(0, 0, 800, 600);
    glFrustum(-x, x, -1.0, 1.0, 4.0, 60.0);
    glMatrixMode(GL_MODELVIEW);
    
//init shader
    GLhandleARB p;
    GLhandleARB v;
    GLhandleARB f;
    GLhandleARB f2;
 char *  vs;
  char *  fs;
  char * fs2;
    //todo test init;
    p = glCreateProgramObjectARB();
    	v = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	f = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	f2 = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
vs = textFileRead("toon.vert");
	fs = textFileRead("cookt.frag");
	fs2 = textFileRead("toon2.frag");
const char * vv = vs;
// printf(fs);
	const char * ff = fs;
	const char * ff2 = fs2;
glShaderSourceARB(v, 1, &vv,NULL);
	glShaderSourceARB(f, 1, &ff,NULL);
	glShaderSourceARB(f2, 1, &ff2,NULL);

glCompileShaderARB(v);
CheckGLSLError(v, GL_OBJECT_COMPILE_STATUS_ARB);

	glCompileShaderARB(f);
CheckGLSLError(f, GL_OBJECT_COMPILE_STATUS_ARB);

	glCompileShaderARB(f2);
CheckGLSLError(f2, GL_OBJECT_COMPILE_STATUS_ARB);

	glAttachObjectARB(p,f);
	glAttachObjectARB(p,f2);
glAttachObjectARB(p,v);



glLinkProgramARB(p);
  CheckGLSLError(p, GL_OBJECT_LINK_STATUS_ARB);

glUseProgramObjectARB(p);

    //------
    Xrotate = 0.0f;
    Yrotate = 0.0f;
    Zrotate = 0.0f;  
    bool rot_left,rot_right,rot_up,rot_down;
    rot_left = false;
    rot_right = false;
    rot_up = false;
    rot_down = false; 
bool wire;
 bool vsh;
wire = false;
while (runing ) 
	{
	  if (rot_left)
	    Yrotate-=0.1f;
	  if (rot_right)
	    Yrotate+=0.1f;
	  if (rot_up)
	    Zrotate-=0.1f;
	  if (rot_down)
	    Zrotate+=0.1f;
	DrawScene();
	while(SDL_PollEvent(&event))
		{
		 switch(event.type)
			{
			case SDL_KEYUP:
			  switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
				  rot_left = false;
				  break;
				case SDLK_RIGHT:
				  rot_right = false;
				  break;
				case SDLK_UP:
				
				  rot_up = false;
				  break;
				case SDLK_DOWN:
				  rot_down = false;
				  break;
				default:  
				  break;
				}
		
			  break;
			case SDL_KEYDOWN:
			 switch (event.key.keysym.sym)
				{
				case SDLK_RIGHT:
				  rot_right = true;
				  break;

				case SDLK_LEFT:
				  rot_left = true;
				break;
				case SDLK_ESCAPE:
					printf("exiting\n");
					runing = false;
				break;
				case SDLK_F3:
				if (vsh)
glUseProgramObjectARB(p);
				else
glUseProgramObjectARB(0);
				  vsh != vsh; 
				 break;
				case SDLK_F2:
				if (wire)
					
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				else
					
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				 wire = !wire;
				break;
				case SDLK_UP:
				  rot_up =true;
				  break;
				case SDLK_DOWN:
				  rot_down = true;
				  break;	
				default:
				break;
				}
			break;	
			case SDL_QUIT:
			runing = 0;
			break;
			default:
			break;
			}
		}	
	}
    SDL_Quit();	
    return 0;
}
