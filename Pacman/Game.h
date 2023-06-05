#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

//additional header files
#include "Vector2.h"

struct GameObject {
    Vector2 pos;
    SDL_Rect rect;
    float moveSpeed;
};

struct TravelPoint {
    Vector2 pos;
    TravelPoint* up;
    TravelPoint* down;
    TravelPoint* right;
    TravelPoint* left;
};

bool Initialize();
void RunLoop();
void ShutDown();

void ProcessInput();
void UpdateGame();
void GenerateOutput();
void DisplayText();
void InitSDLText();
void StartingText();
void EndingText();
void ResetGame();
Vector2 MoveTowards(TravelPoint currentPoint, TravelPoint targetPoint, Vector2 currentPosition, float maxDistanceDelta);
void Move();
TravelPoint ChooseNextTravelPoint(Vector2 nextDirection);
void EnemyMove();
TravelPoint EnemyChooseNextTravelPoint();

class Game {
    public:
        Game():mWindow(nullptr), mIsRunning(true) {
            mTicksCount = 0;
        }

        ~Game() { }

        bool Initialize();
        void RunLoop();
        void ShutDown();

    private:
        //used to track state of snake
        enum State {
            EActive,
            EPaused,
            EDead
        };

        Vector2 currentDirection = Vector2(0,-1), nextDirection = Vector2(0,0), previousDirection = Vector2(0,0), currentEnemyDirection = Vector2(-1,0), nextEnemyDirection = Vector2(0,0);

        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;

        Uint32 mTicksCount;

        float thickness = 16.0f, deltaTime, previousDistance = 1.05f;
        
        bool mIsRunning, gameOver = false, startGame = false;

        std::vector<SDL_Rect> walls;

        std::vector<TravelPoint> travelpoints;
        std::vector<TravelPoint> targetsThatWork;

        TravelPoint currentPoint, targetPoint, previousPoint, enemyCurrentPoint, enemyTargetPoint, enemyPreviousPoint;

        GameObject player, enemy;

        std::vector<GameObject> enemies;
        std::vector<TravelPoint> enemyCurrentPoints;
        std::vector<TravelPoint> enemyTargetPoints;
        std::vector<TravelPoint> enemyPreviousPoints;

        void ProcessInput();
        void UpdateGame();
        void GenerateOutput();
        void DisplayText();
        void InitSDLText();
        void StartingText();
        void EndingText();
        void ResetGame();

        Vector2 MoveTowards(TravelPoint currentPoint, TravelPoint targetPoint, Vector2 currentPosition, float maxDistanceDelta);
        void Move();
        TravelPoint ChooseNextTravelPoint(Vector2 nextDirection);
        void EnemyMove();
        TravelPoint EnemyChooseNextTravelPoint();

        //initialize travelpoints
        TravelPoint pointNULL = {
            Vector2(0,0),
            NULL,
            NULL,
            NULL,
            NULL
        };
        TravelPoint point0 = {
            Vector2(40,40),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point1 = {
            Vector2(150,40),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point2 = {
            Vector2(730,40),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point3 = {
            Vector2(650,40),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point4 = {
            Vector2(150,180),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point5 = {
            Vector2(650,180),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point6 = {
            Vector2(150,300),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point7 = {
            Vector2(650,300),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point8 = {
            Vector2(150,500),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point9 = {
            Vector2(650,500),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point10 = {
            Vector2(150,600),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point11 = {
            Vector2(650,600),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point12 = {
            Vector2(150,710),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point13 = {
            Vector2(650,710),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point14 = {
            Vector2(40,710),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point15 = {
            Vector2(730,710),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point16 = {
            Vector2(400,600),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point17 = {
            Vector2(400,180),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point18 = {
            Vector2(400,300),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point19 = {
            Vector2(400,500),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point20 = {
            Vector2(270,500),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point21 = {
            Vector2(270,300),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point22 = {
            Vector2(540,500),
            NULL,
            NULL,
            NULL,
            NULL,
        };
        TravelPoint point23 = {
            Vector2(540,300),
            NULL,
            NULL,
            NULL,
            NULL,
        };
  
    
};

bool Game::Initialize() {
    //random number generator seed
    srand (time(NULL));

    //initialize SDL library
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    //Initialize text
    //InitSDLText();

    if(sdlResult != 0) {
        //initialization failed
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    //if initialization successful, create window
    mWindow = SDL_CreateWindow(
        "Pacman",
        100,
        100,
        800,
        800,
        0 // Flags
    );

    if(!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(
        mWindow,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC //initialization flags. use accelerated renderer and enable vsync
    );

    //initialize player
    player.pos = Vector2(40,710);
    player.rect.x = player.pos.x;
    player.rect.y = player.pos.y;
    player.rect.w = 40;
    player.rect.h = 40;

    //initialize enemies
    enemy.pos = Vector2(730,40);
    enemy.rect.x = enemy.pos.x;
    enemy.rect.y = enemy.pos.y;
    enemy.rect.w = 40;
    enemy.rect.h = 40;

    /* enemy2.pos = Vector2(40,40);
    enemy2.rect.x = enemy2.pos.x;
    enemy2.rect.y = enemy2.pos.y;
    enemy2.rect.w = 40;
    enemy2.rect.h = 40; */

    //enemies.push_back(enemy1);
    //enemies.push_back(enemy2);

    //update travelpoints
    point0.right = &point1;
    point0.down = &point14;
    point0.up = &pointNULL;
    point0.left = &pointNULL;
    point1.left = &point0;
    point1.down = &point4;
    point1.right = &point3;
    point1.up = &pointNULL;
    point2.left = &point3;
    point2.down = &point15;
    point2.up = &pointNULL;
    point2.right = &pointNULL;
    point3.left = &point1;
    point3.right = &point2;
    point3.down = &point5;
    point3.up = &pointNULL;
    point4.up = &point1;
    point4.down = &point6;
    point4.right = &point17;
    point4.left = &pointNULL;
    point5.left = &point17;
    point5.up = &point3;
    point5.down = &point7;
    point5.right = &pointNULL;
    point6.up = &point4;
    point6.down = &point8;
    point6.right = &point21;
    point6.left = &pointNULL;
    point7.up = &point5;
    point7.left = &point23;
    point7.down = &point9;
    point7.right = &pointNULL;
    point8.up = &point6;
    point8.right = &point20;
    point8.down = &point10;
    point8.left = &pointNULL;
    point9.up = &point7;
    point9.down = &point11;
    point9.left = &point22;
    point9.right = &pointNULL;
    point10.up = &point8;
    point10.down = &point12;
    point10.right = &point16;
    point10.left = &pointNULL;
    point11.up = &point9;
    point11.down = &point13;
    point11.left = &point16;
    point11.right = &pointNULL;
    point12.up = &point10;
    point12.left = &point14;
    point12.right = &point13;
    point12.down = &pointNULL;
    point13.up = &point11;
    point13.right = &point15;
    point13.left = &point12;
    point13.down = &pointNULL;
    point14.up = &point0;
    point14.right = &point12;
    point14.down = &pointNULL;
    point14.left = &pointNULL;
    point15.up = &point2;
    point15.left = &point13;
    point15.down = &pointNULL;
    point15.right = &pointNULL;
    point16.up = &point19;
    point16.left = &point10;
    point16.right = &point11;
    point16.down = &pointNULL;
    point17.left = &point4;
    point17.right = &point5;
    point17.down = &point18;
    point17.up = &pointNULL;
    point18.right = &point23;
    point18.left = &point21;
    point18.down = &point19;
    point18.up = &point17;
    point19.up = &point18;
    point19.left = &point20;
    point19.right = &point22;
    point19.down = &point16;
    point20.up = &point21;
    point20.right = &point19;
    point20.left = &point8;
    point20.down = &pointNULL;
    point21.left = &point6;
    point21.down = &point20;
    point21.right = &point18;
    point21.up = &pointNULL;
    point22.up = &point23;
    point22.right = &point9;
    point22.left = &point19;
    point22.down = &pointNULL;
    point23.down = &point22;
    point23.left = &point18;
    point23.right = &point7;
    point23.up = &pointNULL;


    //add to vector
    travelpoints.push_back(point0);
    travelpoints.push_back(point1);
    travelpoints.push_back(point2);
    travelpoints.push_back(point3);
    travelpoints.push_back(point4);
    travelpoints.push_back(point5);
    travelpoints.push_back(point6);
    travelpoints.push_back(point7);
    travelpoints.push_back(point8);
    travelpoints.push_back(point9);
    travelpoints.push_back(point10);
    travelpoints.push_back(point11);
    travelpoints.push_back(point12);
    travelpoints.push_back(point13);
    travelpoints.push_back(point14);
    travelpoints.push_back(point15);
    travelpoints.push_back(point16);
    travelpoints.push_back(point17);
    travelpoints.push_back(point18);
    travelpoints.push_back(point19);
    travelpoints.push_back(point20);
    travelpoints.push_back(point21);
    travelpoints.push_back(point22);
    travelpoints.push_back(point23);

    //env
    SDL_Rect oneWall = {100,40 * 3,thickness,800 - 40 * 6};
    walls.push_back(oneWall);
    SDL_Rect oneWall1 = {700,40 * 3,thickness,800 - 40 * 6};
    walls.push_back(oneWall1);
    SDL_Rect oneWall2 = {210,125,800 - 40 * 10,thickness};
    walls.push_back(oneWall2);
    SDL_Rect oneWall3 = {210,675,800 - 40 * 10,thickness};
    walls.push_back(oneWall3);
    SDL_Rect oneWall4 = {210,250,800 - 40 * 16.5,thickness};
    walls.push_back(oneWall4);
    SDL_Rect oneWall5 = {470,250,800 - 40 * 16.5,thickness};
    walls.push_back(oneWall5);
    SDL_Rect oneWall6 = {210,550,800 - 40 * 16.5,thickness};
    walls.push_back(oneWall6);
    SDL_Rect oneWall7 = {470,550,800 - 40 * 16.5,thickness};
    walls.push_back(oneWall7);
    SDL_Rect oneWall8 = {210,350,thickness,800 - 40 * 17};
    walls.push_back(oneWall8);
    SDL_Rect oneWall9 = {470,350,thickness,800 - 40 * 17};
    walls.push_back(oneWall9);
    SDL_Rect oneWall10 = {330,350,thickness,800 - 40 * 17};
    walls.push_back(oneWall10);
    SDL_Rect oneWall11 = {330 + (470 - 210),350,thickness,800 - 40 * 17};
    walls.push_back(oneWall11);

    //player starting point and initial target point
    currentPoint = point14;
    targetPoint = point12;
    previousPoint = currentPoint;

    //enemies starting info
    enemyCurrentPoint = point3;
    enemyTargetPoint = point3;
    enemyPreviousPoint = enemyCurrentPoint;


    //enemyCurrentPoints.push_back(enemyCurrentPoint1);
    //enemyCurrentPoints.push_back(enemyCurrentPoint2);

    //enemyTargetPoints.push_back(enemyTargetPoint1);
    //enemyTargetPoints.push_back(enemyTargetPoint2);

    //enemyPreviousPoints.push_back(enemyPreviousPoint1);
    //enemyPreviousPoints.push_back(enemyPreviousPoint2);

    return true;
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ShutDown() {
    //destroy SDL_Window
    SDL_DestroyWindow(mWindow);

    //destroy SDL_Renderer
    SDL_DestroyRenderer(mRenderer);

    //close SDL
    SDL_Quit();
}

void Game::ProcessInput() {
    SDL_Event event;

    //go through all events and respond as desired/appropriate
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;
            case SDL_KEYDOWN:
                switch( event.key.keysym.sym ) {
                    case SDLK_SPACE:
                        break;
                    case SDLK_UP:
                        nextDirection = Vector2(0,1);
                        break;
                    case SDLK_DOWN:
                        nextDirection = Vector2(0,-1);
                        break;
                    case SDLK_RIGHT:
                        nextDirection = Vector2(1,0);
                        break;
                    case SDLK_LEFT:
                        nextDirection = Vector2(-1,0);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    // Retrieve the state of all of the keys then scan each as desired
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_ESCAPE]){
        mIsRunning = false;
    }

}

void Game::UpdateGame() {
    //update frame at fixed intervals (fixedDeltaTime)
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    //get deltaTime
    deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    mTicksCount = SDL_GetTicks();

    //clamp deltaTime
    if(deltaTime > .05f) {
        deltaTime = 0.05f;
    }

    //updated player movement
    Move();
    player.rect.x = player.pos.x;
    player.rect.y = player.pos.y;

    //update enemy movement
    EnemyMove();
    enemy.rect.x = enemy.pos.x;
    enemy.rect.y = enemy.pos.y;
    //enemy2.rect.x = enemy2.pos.x;
    //enemy2.rect.y = enemy2.pos.y;

    /* for(int i = 0; i < enemies.size(); i++) {
        EnemyMove(enemies[i], enemyTargetPoints[i],enemyCurrentPoints[i], enemyPreviousPoints[i]);
        enemies[i].rect.x = enemies[i].pos.x;
        enemies[i].rect.y = enemies[i].pos.y;
        //std::cout << "OUTSIDE: " << enemies[i].pos.x << "," << enemies[i].pos.y << std::endl;
    } */
    
}
/* 
void Game::EnemyMove() {

    if(enemy1.pos != enemyTargetPoint1.pos && enemyTargetPoint1.pos != Vector2(0,0)) {
        enemy1.pos = MoveTowards(enemyCurrentPoint1,enemyTargetPoint1, enemy1.pos, 3.0f);
    }
    //if player is at target, update current to target
    else if(enemy1.pos == enemyTargetPoint1.pos) {
        enemyPreviousPoint1 = enemyCurrentPoint1;
        enemyCurrentPoint1 = enemyTargetPoint1;
        enemyTargetPoint1 = EnemyChooseNextTravelPoint(enemyCurrentPoint1, currentEnemyDirection1, nextEnemyDirection1); //use vectors instead of enum for direction
    }

    if(enemy2.pos != enemyTargetPoint2.pos && enemyTargetPoint2.pos != Vector2(0,0)) {
        enemy2.pos = MoveTowards(enemyCurrentPoint2,enemyTargetPoint2, enemy2.pos, 3.0f);
    }
    //if player is at target, update current to target
    else if(enemy2.pos == enemyTargetPoint2.pos) {
        enemyPreviousPoint2 = enemyCurrentPoint2;
        enemyCurrentPoint2 = enemyTargetPoint2;
        enemyTargetPoint2 = EnemyChooseNextTravelPoint(enemyCurrentPoint2, currentEnemyDirection2, nextEnemyDirection2); //use vectors instead of enum for direction
    }
}

TravelPoint Game::EnemyChooseNextTravelPoint(TravelPoint enemyCurrentPoint, Vector2 currentEnemyDirection, Vector2 nextEnemyDirection) {
    TravelPoint tempTargetPoint = {
        Vector2(0,0),
        NULL,
        NULL,
        NULL,
        NULL,
    };

    targetsThatWork.clear();

    TravelPoint neighborTargets[4] = {
        *(enemyCurrentPoint.up),
        *(enemyCurrentPoint.down),
        *(enemyCurrentPoint.right),
        *(enemyCurrentPoint.left)
    };
    
    Vector2 directions[4] = {
        Vector2(0,1),
        Vector2(0,-1),
        Vector2(1,0),
        Vector2(-1,0)
    };

    float maxDistance = 10000.0f;

    for(int i = 0; i < 4; i++) {
        Vector2 tempDir = Vector2(-1.0f * currentEnemyDirection.x, -1.0f * currentEnemyDirection.y);
        if(neighborTargets[i].pos != pointNULL.pos && directions[i] != tempDir) {
            float distanceFromTarget = sqrt(pow(neighborTargets[i].pos.x - targetPoint.pos.x,2) + pow(neighborTargets[i].pos.y - targetPoint.pos.y,2));
            if(distanceFromTarget <= maxDistance) {
                targetsThatWork.push_back(neighborTargets[i]);
                maxDistance = distanceFromTarget;
                tempTargetPoint = neighborTargets[i];
                nextEnemyDirection = directions[i];
            }
        }
    }

    currentEnemyDirection = nextEnemyDirection;

    return tempTargetPoint;     
}
 */
void Game::EnemyMove() {

    if(enemy.pos != enemyTargetPoint.pos && enemyTargetPoint.pos != Vector2(0,0)) {
        enemy.pos = MoveTowards(enemyCurrentPoint,enemyTargetPoint, enemy.pos, 3.0f);
        //std::cout << "INSIDE: " << enemyX.pos.x << "," << enemyX.pos.y << std::endl;
    }
    //if player is at target, update current to target
    else if(enemy.pos == enemyTargetPoint.pos) {
        enemyPreviousPoint = enemyCurrentPoint;
        enemyCurrentPoint = enemyTargetPoint;
        enemyTargetPoint = EnemyChooseNextTravelPoint(); //use vectors instead of enum for direction
    }
}

TravelPoint Game::EnemyChooseNextTravelPoint() {
    TravelPoint tempTargetPoint = {
        Vector2(0,0),
        NULL,
        NULL,
        NULL,
        NULL,
    };

    targetsThatWork.clear();

    TravelPoint neighborTargets[4] = {
        *(enemyCurrentPoint.up),
        *(enemyCurrentPoint.down),
        *(enemyCurrentPoint.right),
        *(enemyCurrentPoint.left)
    };
    
    Vector2 directions[4] = {
        Vector2(0,1),
        Vector2(0,-1),
        Vector2(1,0),
        Vector2(-1,0)
    };

    float maxDistance = 10000.0f;

    for(int i = 0; i < 4; i++) {
        Vector2 tempDir = Vector2(-1.0f * currentEnemyDirection.x, -1.0f * currentEnemyDirection.y);
        if(neighborTargets[i].pos != pointNULL.pos && directions[i] != tempDir) {
            float distanceFromTarget = sqrt(pow(neighborTargets[i].pos.x - targetPoint.pos.x,2) + pow(neighborTargets[i].pos.y - targetPoint.pos.y,2));
            if(distanceFromTarget <= maxDistance) {
                targetsThatWork.push_back(neighborTargets[i]);
                maxDistance = distanceFromTarget;
                tempTargetPoint = neighborTargets[i];
                nextEnemyDirection = directions[i];
            }
        }
    }

    currentEnemyDirection = nextEnemyDirection;

    return tempTargetPoint;     
}

void Game::Move() {
    if(player.pos != targetPoint.pos && targetPoint.pos != Vector2(0,0)) {
        player.pos = MoveTowards(currentPoint,targetPoint, player.pos, 5.0f);
    }
    //if player is at target, update current to target
    else if(player.pos == targetPoint.pos) {
        previousPoint = currentPoint;
        currentPoint = targetPoint;
        targetPoint = ChooseNextTravelPoint(nextDirection); //use vectors instead of enum for direction
    } 
    
    if(nextDirection == currentDirection * -1.0f) { // reverse
        currentDirection = nextDirection;
        nextDirection = Vector2(0,0);
        previousPoint = targetPoint;
        targetPoint = currentPoint;
        currentPoint = previousPoint;
    }
}

TravelPoint Game::ChooseNextTravelPoint(Vector2 nextDirection) {
    TravelPoint tempTargetPoint = {
        Vector2(0,0),
        NULL,
        NULL,
        NULL,
        NULL,
    };

    TravelPoint neighborTargets[4] = {
        *(currentPoint.up),
        *(currentPoint.down),
        *(currentPoint.right),
        *(currentPoint.left)
    };
    
    Vector2 directions[4] = {
        Vector2(0,1),
        Vector2(0,-1),
        Vector2(1,0),
        Vector2(-1,0)
    };

    if(nextDirection == Vector2(0,0)) {
        //std::cout << "NO NEXT DIR" << std::endl;

        int currentDirectionIndex = 0;

        //see which direction nextDirection is
        for(int i = 0; i < 4; i++) {
            if(currentDirection == directions[i]) {
                currentDirectionIndex = i;
            }
        }
        //if not, check if current direction is available
        if(neighborTargets[currentDirectionIndex].pos != pointNULL.pos) {
            tempTargetPoint= neighborTargets[currentDirectionIndex];
            previousDistance = 1.05f;
            return tempTargetPoint;
        }
        else {
            return currentPoint;
        }
    }

    else if(nextDirection != Vector2(0,0)) {
        //std::cout << "YESSSSS NEXT DIR" << std::endl;

        int nextDirectionIndex = 0, currentDirectionIndex = 0;

        //see which direction nextDirection is
        for(int i = 0; i < 4; i++) {
            if(nextDirection == directions[i]) {
                nextDirectionIndex = i;
            }
            if(currentDirection == directions[i]) {
                currentDirectionIndex = i;
            }
        }

        //check if nextDirection yields a valid node
        if(neighborTargets[nextDirectionIndex].pos != pointNULL.pos) {
            //set new direction and reset nextDirection
            tempTargetPoint = neighborTargets[nextDirectionIndex];
            currentDirection = nextDirection;
            nextDirection = Vector2(0,0);
            previousDistance = 1.05f;
            return tempTargetPoint;
        }
        //if not, check if current direction is available
        else if(neighborTargets[currentDirectionIndex].pos != pointNULL.pos) {
            tempTargetPoint = neighborTargets[currentDirectionIndex];
            previousDistance = 1.05f;
            return tempTargetPoint;
        }
        else {
            return currentPoint;
        }
    } 

    return currentPoint;   
}

Vector2 Game::MoveTowards(TravelPoint currentPoint, TravelPoint targetPoint, Vector2 currentPosition, float maxDistanceDelta) {
    Vector2 a = Vector2(targetPoint.pos.x - currentPosition.x,targetPoint.pos.y - currentPosition.y);
    float magnitude = sqrt((a.x*a.x) + (a.y*a.y));
    if (magnitude <= maxDistanceDelta || magnitude == 0.0f)
    {
        return targetPoint.pos;
    }
    Vector2 target = currentPosition + a * (1 / magnitude * maxDistanceDelta);
    return target;
}

void Game::GenerateOutput() {

    SDL_SetRenderDrawColor(mRenderer,0,0,0,0);

    SDL_RenderClear(mRenderer); //clear back buffer to current draw color

    SDL_SetRenderDrawColor(mRenderer,255,255,255,255);

    SDL_Rect topWall = {0,0,1024,thickness};
    SDL_Rect bottomWall = {0,800 - 2 * thickness,1024,thickness};
    SDL_Rect leftWall = {0,0,thickness,768};
    SDL_Rect rightWall = {800 - thickness,0,thickness,768};

    SDL_RenderFillRect(mRenderer,&topWall);
    SDL_RenderFillRect(mRenderer,&rightWall);
    SDL_RenderFillRect(mRenderer,&leftWall);
    SDL_RenderFillRect(mRenderer,&bottomWall);

    //draw travelpoints
    /* for(int i = 0; i < travelpoints.size(); i++) {
        SDL_Rect rect = {travelpoints[i].pos.x,travelpoints[i].pos.y,20,20};
        SDL_RenderFillRect(mRenderer,&rect);
    } */

    //draw env walls
    for(int i = 0; i < walls.size(); i++) {
        SDL_RenderFillRect(mRenderer,&walls[i]);
    }

    //draw player
    SDL_RenderFillRect(mRenderer,&player.rect);

    SDL_SetRenderDrawColor(mRenderer,255,0,0,255);

    //draw enemies
    /* for(int i = 0; i < enemies.size(); i++) {
        SDL_RenderFillRect(mRenderer,&enemies[i].rect);
    } */
    
    SDL_RenderFillRect(mRenderer,&enemy.rect);//SDL_RenderFillRect(mRenderer,&enemy2.rect);

    SDL_SetRenderDrawColor(mRenderer,255,0,0,255);

    SDL_RenderPresent(mRenderer); //swap front and back buffers

    //DisplayText();
} 


/* 
void Game::InitSDLText() {
    //initialize, else load error
    if(TTF_Init() == -1) {
        std::cout << "Failed to initialize text.Error: " << TTF_GetError() << std::endl;
    }
}

void Game::ResetGame() {

}

void Game::StartingText() {
    SDL_SetRenderDrawColor( //pointer, RGBA
            mRenderer,
            0,
            0,
            0,
            0
        );

        SDL_RenderClear(mRenderer);

        //draw game scene
        SDL_SetRenderDrawColor( //pointer, RGBA
            mRenderer,
            255,
            255,
            255,
            255
        );

        TTF_Font* ourFont;
        SDL_Surface * titleSurfaceText;	
        SDL_Surface * optionSurfaceText;
        SDL_Texture * titleTexture;
        SDL_Texture * optionTexture;

        SDL_Rect titleText = {340,100,300,200};
        SDL_Rect optionText = {250,400,500,100};

        //load font file and set size
        ourFont = TTF_OpenFont("AldotheApache.ttf",1000);

        //confirm font loaded
        if(ourFont == nullptr) {
            std::cout << "Could not load font" << std::endl;
            exit(1);
        }

        SDL_Color textColor = {255,255,255,255};

        //pixels from text
        titleSurfaceText = TTF_RenderText_Solid(ourFont,"JUMP!",textColor);
        optionSurfaceText = TTF_RenderText_Solid(ourFont,"HIT SPACEBAR TO PLAY",textColor);

        //set up texture
        titleTexture = SDL_CreateTextureFromSurface(mRenderer,titleSurfaceText);
        optionTexture = SDL_CreateTextureFromSurface(mRenderer,optionSurfaceText);

        SDL_FreeSurface(titleSurfaceText);
        SDL_FreeSurface(optionSurfaceText);

        SDL_RenderCopy(mRenderer,titleTexture,NULL,&titleText);
        SDL_RenderCopy(mRenderer,optionTexture,NULL,&optionText);

        //destroy texture
        SDL_DestroyTexture(titleTexture);
        SDL_DestroyTexture(optionTexture);

        //close font
        TTF_CloseFont(ourFont);

        SDL_RenderPresent(mRenderer); //swap front and back buffers
}

void Game::EndingText() {
        SDL_SetRenderDrawColor( //pointer, RGBA
            mRenderer,
            0,
            0,
            0,
            0
        );

        SDL_RenderClear(mRenderer);

        //draw game scene
        SDL_SetRenderDrawColor( //pointer, RGBA
            mRenderer,
            255,
            255,
            255,
            255
        );
        TTF_Font* ourFont;
        SDL_Surface * titleSurfaceText;	
        SDL_Surface * optionSurfaceText;
        SDL_Texture * titleTexture;
        SDL_Texture * optionTexture;

        SDL_Rect titleText = {340,100,300,200};
        SDL_Rect optionText = {250,400,500,100};

        //load font file and set size
        ourFont = TTF_OpenFont("AldotheApache.ttf",1000);

        //confirm font loaded
        if(ourFont == nullptr) {
            std::cout << "Could not load font" << std::endl;
            exit(1);
        }

        SDL_Color textColor = {255,255,255,255};

        //pixels from text
        titleSurfaceText = TTF_RenderText_Solid(ourFont,"JUMP!",textColor);
        optionSurfaceText = TTF_RenderText_Solid(ourFont,"EVERYONE WINS! A FOR EFFORT",textColor);

        //set up texture
        titleTexture = SDL_CreateTextureFromSurface(mRenderer,titleSurfaceText);
        optionTexture = SDL_CreateTextureFromSurface(mRenderer,optionSurfaceText);

        SDL_FreeSurface(titleSurfaceText);
        SDL_FreeSurface(optionSurfaceText);

        SDL_RenderCopy(mRenderer,titleTexture,NULL,&titleText);
        SDL_RenderCopy(mRenderer,optionTexture,NULL,&optionText);

        //destroy texture
        SDL_DestroyTexture(titleTexture);
        SDL_DestroyTexture(optionTexture);

        //close font
        TTF_CloseFont(ourFont);

        SDL_RenderPresent(mRenderer); //swap front and back buffers
        
}

void Game::DisplayText() {
    //add text
    TTF_Font* ourFont;
    SDL_Surface * playerSurfaceText;	
    SDL_Surface * AISurfaceText;
    SDL_Texture * playerTexture;
    SDL_Texture * AITexture;

    SDL_Rect playerScoreText = {950,25,50,50};

    //load font file and set size
    ourFont = TTF_OpenFont("AldotheApache.ttf",1000);

    //confirm font loaded
    if(ourFont == nullptr) {
        std::cout << "Could not load font" << std::endl;
        exit(1);
    }

    SDL_Color textColor = {255,255,255,255};

    playerScoreStr = std::to_string(playerScore);
    char const *pchar = playerScoreStr.c_str();  //use char const* as target type

    //pixels from text
    playerSurfaceText = TTF_RenderText_Solid(ourFont,pchar,textColor);

    //set up texture
    playerTexture = SDL_CreateTextureFromSurface(mRenderer,playerSurfaceText);

    SDL_FreeSurface(playerSurfaceText);

    SDL_RenderCopy(mRenderer,playerTexture,NULL,&playerScoreText);

    //destroy texture
    SDL_DestroyTexture(playerTexture);

    //close font
    TTF_CloseFont(ourFont);

    SDL_RenderPresent(mRenderer); //swap front and back buffers
}
 */