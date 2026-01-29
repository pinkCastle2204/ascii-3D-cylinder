#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

int main(){
    //rendering variables
    const int HEIGHT = 40;
    const int WIDTH = 120;
    const int WIDTH_with_newline = WIDTH + 1;
    const float pi = 3.14159265359f;
    const float aspectCorrection = 0.5f;

    int cX = WIDTH / 2;
    int cY = HEIGHT / 2;
    float K = 40.0f;
    float cameraDistance = 25.0f;
    
    //geometry variables
    const float r = 10.0f;
    const float H = 20.0f;
    float step = 0.5f;

    //shading
    const char ASCIIramp[] = ".,-~:;=!*#$@";
    const int rampSize = sizeof(ASCIIramp) - 1;

    char SCREEN[HEIGHT * (WIDTH + 1)];
    float zBuffer[HEIGHT * WIDTH];

    //angles
    float Ax = 0.0f;
    float Ay = 0.0f;
    float Az = 0.0f;

    // ANSI code to clear the terminal
    printf("\x1b[2J");

    //animation loop
    while (true) {

        //clears SCREEN buffer
        memset(SCREEN, ' ', sizeof(SCREEN));
        for (int i = 0; i < HEIGHT; i++) {
            SCREEN[i * WIDTH_with_newline + WIDTH] = '\n';
        }
        for (int i = 0; i < HEIGHT * WIDTH; i++) {
            zBuffer[i] = 0.0f;
        }

        //draws cylinder
        for(float y = -H / 2.0f; y < H / 2.0f; y += step){
            for(float theta = 0.0f; theta < 2 * pi; theta += 0.01f){

                //cylinder
                float x = r * cos(theta);
                float z = r * sin(theta);

                //rotation
                // Rotate around X
                float y1 = y * cos(Ax) - z * sin(Ax);
                float z1 = y * sin(Ax) + z * cos(Ax);

                // Rotate around Y
                float x2 = x * cos(Ay) + z1 * sin(Ay);
                float z2 = -x * sin(Ay) + z1 * cos(Ay);

                // Rotate around Z
                float x3 = x2 * cos(Az) - y1 * sin(Az);
                float y3 = x2 * sin(Az) + y1 * cos(Az);
            
                float ZCam = cameraDistance + z2;
                if (ZCam <= 0.1f) continue;

                int screenSpaceX = (int)(cX + (K * x3 / ZCam));
                int screenSpaceY = (int)(cY + (K * y3 / ZCam) * aspectCorrection);

                if (screenSpaceX < 0 || screenSpaceX >= WIDTH ||
                    screenSpaceY < 0 || screenSpaceY >= HEIGHT)
                    continue;

                //normals based shading
                float nz = sin(theta);
                float brightness = -nz;
                float light = (brightness + 1.0f) * 0.5f;

                if (light < 0) light = 0;
                if (light > 1) light = 1;

                int shadeIndex = (int)(light * (rampSize - 1));
                char shade = ASCIIramp[shadeIndex];

                //Z-Buffer
                int zIndex = screenSpaceY * WIDTH + screenSpaceX;
                float invZ = 1.0f / ZCam;

                if (invZ > zBuffer[zIndex]) {
                    zBuffer[zIndex] = invZ;
                    SCREEN[screenSpaceY * WIDTH_with_newline + screenSpaceX] = shade;
                }
            }
        }

        //output to terminal
        printf("\x1b[H"); // ANSI escape code to move cursor to top-left
        fwrite(SCREEN, 1, sizeof(SCREEN), stdout);

        //angle increment
        Ax += 0.02f;
        Ay += 0.03f;
        Az += 0.015f;

        //delay
        #ifdef _WIN32
            Sleep(16);      
        #else
            usleep(16000);  
        #endif
    }

    return 0;
}
