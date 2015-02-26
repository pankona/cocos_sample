#include "GameControl.h"
#include <stdio.h>

void
GameControl::update(float delta) {
    mm.progress(delta);

    // these should be treated on callback from model manager.
    vm.setBarPosition(mm.getBarPosition());
    vm.setBallPosition(mm.getBallPosition());

    collidedBlockNum = 0;
    vm.updateView();
}

void
GameControl::initialize(Scene* baseScene) {
    mm.initialize();
    mm.addModelManagerEventListener(this);
    vm.initialize(baseScene);
    vm.addViewManagerEventListener(this);

    // get screen size
    Size screenSize = Director::getInstance()->getVisibleSize();
    vm.initializeField((int) screenSize.width, (int) screenSize.height);
    mm.setFieldSize((int) screenSize.width, (int) screenSize.height);
    log ("set screen size w = %d, h = %d", (int) screenSize.width, (int) screenSize.height) ;

    mm.initializeBar();
    vm.initializeBar(mm.getBarWidth(), mm.getBarHeight(), mm.getBarPosition());
    log ("bar initialized with parameter: w = %d, h = %d, p = (%d, %d)", mm.getBarWidth(), mm.getBarHeight(), mm.getBarPosition().x, mm.getBarPosition().y);

    mm.initializeBall();
    vm.initializeBall(mm.getBallRadius(), mm.getBallPosition());
    log ("ball initialized with parameter: r = %d, p = (%d, %d)", mm.getBallRadius(), mm.getBallPosition().x, mm.getBallPosition().y);

    mm.initializeBlocks();
    for (int i = 0; i < mm.getBlockNum(); i++) {
        vm.addBlock(mm.getBlockWidth(i), mm.getBlockHeight(i), mm.getBlockPosition(i));

        // temporary implementation. set colors to blocks.
        switch (i % 4) {
            case 0:
                vm.setBlockColor(i, Color3B::BLUE);
                break;
            case 1:
                vm.setBlockColor(i, Color3B::MAGENTA);
                break;
            case 2:
                vm.setBlockColor(i, Color3B::GRAY);
                break;
            case 3:
                vm.setBlockColor(i, Color3B::ORANGE);
                break;
            default:
                vm.setBlockColor(i, Color3B::BLACK);
                break;
        }
    }
}

void
GameControl::onViewManagerEvent(ViewManagerEvent in_event, void* arg) {

    Position *p;

    switch (in_event) {
        case ViewManagerEvent::BALL_AND_BAR_COLLISION:
            mm.onCollisionBallAndBar();
            break;
        case ViewManagerEvent::TOUCH_BEGAN:
            p = (Position*) arg;
            mm.onTouchBegan(p->x, p->y);
            break;
        case ViewManagerEvent::TOUCH_MOVED:
            p = (Position*) arg;
            mm.onTouchMoved(p->x, p->y);
            break;
        case ViewManagerEvent::TOUCH_ENDED:
            mm.onTouchEnded();
            break;
        case ViewManagerEvent::BALL_AND_BLOCK_COLLISION:
            int* blockIndex;
            blockIndex = (int*) arg;

            // only one time ball can turn over by block per one frame.
            bool needBallTurnOver;
            if (collidedBlockNum == 0) {
                needBallTurnOver = true;
            } else {
                needBallTurnOver = false;
            }
            mm.onCollisionBallAndBlock(*blockIndex, needBallTurnOver);
            collidedBlockNum++;
            break;
        default:
            break;
    }
}

void
GameControl::onModelManagerEvent(ModelManagerEvent in_event, void* arg) {
    switch (in_event) {
        case ModelManagerEvent::BLOCK_DIED:
            int* blockIndex;
            blockIndex = (int *)arg;
            vm.markBlockAsKilled(*blockIndex);
            break;
        default:
            break;
    }
}

