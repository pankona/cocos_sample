#ifndef __MODELMANAGER_H__
#define __MODELMANAGER_H__

#include "Field.h"
#include "Bar.h"
#include "Ball.h"
#include "Block.h"
#include "Player.h"
#include "ModelManagerEventListener.h"
#include <vector>

class ModelManager {
private:
    Player* player;
    Field* field;
    Bar* bar;
    Ball* ball;
    std::vector<Block*> blocks;
    int blockNum;
    Position lastTouchedPosition;
    std::vector<ModelManagerEventListener*> listeners;
    Position verticalDrawStart;
    Position verticalDrawEnd;
    bool isBarSwinging;
    int barSwingElapsedFrame;
    int barFollowthroughElapsedFrame;
    int currentSwingState;
    bool isAlreadyHitBySwing;

    bool allBlocksDestroyed();
    bool isTouchOnRightSideOfBar(int);
    void moveBall(float);
    void moveBar(float);
    void eventNotify(ModelManagerEventListener::ModelManagerEvent, void*);
    bool shouldSwingBar(int);
    void startSwinging();
    void endSwinging();
    void progressBarSwinging();
    bool isTimeToFollowThrough(int);
    static const int swingBarAngleTable[];
    bool doCollisionWhileBarSwinging(Position, Position, int*);
    void calculateBallReflection(int);

public:
    ModelManager();
    void initialize();
    void progress(float delta);
    void onTouchBegan(int, int);
    void onTouchMoved(int, int);
    void onTouchEnded();
    void onCollisionBallAndBar();
    void onCollisionBallAndBlock(int, bool);
    bool doCollideBallAndBar();

    void initializeBar();
    Position getBarPosition();
    int getBarWidth();
    int getBarHeight();

    void initializeBall();
    Position getBallPosition();
    int getBallRadius();
    void setBallSpeed(int);
    void resetBall();

    void setBarPositionX(int);
    void setBallPositionX(int);

    void setFieldSize(int, int);

    void initializeBlocks();
    int getBlockNum();
    int getBlockWidth(int);
    int getBlockHeight(int);
    Position getBlockPosition(int);
    void killBlock(int);

    void addModelManagerEventListener(ModelManagerEventListener*);

    void decreasePlayerLife();
    bool isPlayerStillAlive();

    void startVerticalDraw(int);
    void updateVerticalDraw(int);
    void endVerticalDraw();
    int getVerticalDrawDelta();

    bool barSwinging();
};

#endif // __MODELMANAGER_H__
