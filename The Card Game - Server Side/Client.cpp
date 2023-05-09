#include <SDL.h>
#include <SDL_image.h>
#include <SDL_net.h>
#include <iostream>
#include <string>
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Math.h"
#include "GlobalItems.h"

void runRPSClient();
void runRPSClientLocal();

bool hasFront = false;

int frontCounter = 0;

RenderWindow window("The Card Game v1.0", 1280, 720);

int main(int argc, char* argv[]) {

    SDL_Texture* rock = window.loadTexture("assets\\Cards\\Rock.png");
    SDL_Texture* title = window.loadTexture("assets\\Screens\\TitleScreenV1.png");

    Entity card(Vector2f(0, 0), rock, 128, 96, 2);
    Entity titleScreen(Vector2f(0,0), title, 72, 128, 10);

    SDL_Event event;
    SDL_Rect joinButton;
    joinButton.x = 30;
    joinButton.y = 580;
    joinButton.w = 350;
    joinButton.h = 110;

    SDL_Rect testButton;
    testButton.x = 900;
    testButton.y = 580;
    testButton.w = 350;
    testButton.h = 110;

    int response;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int x = event.button.x;
                    int y = event.button.y;
                    if (x >= joinButton.x && x <= joinButton.x + joinButton.w && y >= joinButton.y && y <= joinButton.y + joinButton.h)
                    {
                        // Initialize SDL2's networking subsystem
                        if (SDLNet_Init() < 0) {
                            std::cerr << "SDLNet_Init failed: " << SDLNet_GetError() << std::endl;
                            return 1;
                        }

                        // Set up a client socket and connect to the server
                        IPaddress ip;
                        if (SDLNet_ResolveHost(&ip, "localhost", 1234) < 0) {
                            std::cerr << "SDLNet_ResolveHost failed: " << SDLNet_GetError() << std::endl;
                            SDLNet_Quit();
                            return 1;
                        }
                        TCPsocket clientSocket = SDLNet_TCP_Open(&ip);
                        if (!clientSocket) {
                            std::cerr << "SDLNet_TCP_Open failed: " << SDLNet_GetError() << std::endl;
                            SDLNet_Quit();
                            return 1;
                        }
                        std::cout << "Clicked button " << std::endl;
                        runRPSClient();
                        //int code;
                        //if (std::cin >> code) {
                        //    // Send the message to the server
                        //    int numBytes = SDLNet_TCP_Send(clientSocket, &code, sizeof(code));
                        //    if (false) {
                        //        std::cerr << "SDLNet_TCP_Send failed: " << SDLNet_GetError() << std::endl;
                        //        SDLNet_TCP_Close(clientSocket);
                        //        SDLNet_Quit();
                        //        return 1;
                        //    }
                        //    // Receive a response from the server
                        //    numBytes = SDLNet_TCP_Recv(clientSocket, &response, sizeof(response));
                        //    if (numBytes <= 0) {
                        //        std::cerr << "SDLNet_TCP_Recv failed: " << SDLNet_GetError() << std::endl;
                        //        SDLNet_TCP_Close(clientSocket);
                        //        SDLNet_Quit();
                        //        return 1;
                        //    }
                        //    std::cout << "Server response: " << response << std::endl;
                        //}
                        SDLNet_TCP_Close(clientSocket);
                    }
                    if (x >= testButton.x && x <= testButton.x + testButton.w && y >= testButton.y && y <= testButton.y + testButton.h) {
                        std::cout << "test pressed " << std::endl;
                        runRPSClientLocal();
                    }
                }
                break;
            }
        }
        window.clear();
        window.render(titleScreen);
        window.render(card);
        window.display();
        
    }

    // Clean up
    window.cleanUp();
    SDLNet_Quit();

    return 0;
}

void runRPSClient() {
    bool running = true;

    SDL_Texture* R = window.loadTexture("assets\\Cards\\Rock.png");
    SDL_Texture* P = window.loadTexture("assets\\Cards\\Paper.png");
    SDL_Texture* S = window.loadTexture("assets\\Cards\\Scissors.png");
    SDL_Texture* RPS = window.loadTexture("assets\\Screens\\RPSMainScreen.png");

    Entity rock(Vector2f(32, 64), R, 128, 96, 2);
    Entity paper(Vector2f(96, 64), P, 128, 96, 2);
    Entity scissors(Vector2f(160, 64), S, 128, 96, 2);
    Entity RPSScreen(Vector2f(0, 0), RPS, 72, 128, 10);

    while (running) {
        window.clear();
        window.render(RPSScreen);
        window.render(rock);
        window.render(paper);
        window.render(scissors);
        window.display();
    }
}

void runRPSClientLocal() {
    std::vector<Card> cardsInHand;
    bool running = true;
    SDL_Event event;

    SDL_Texture* RPS = window.loadTexture("assets\\Screens\\RPSMainScreen.png");
    Entity RPSScreen(Vector2f(0, 0), RPS, 72, 128, 10);

    {
        SDL_Texture* R = window.loadTexture("assets\\Cards\\Rock.png");
        SDL_Texture* P = window.loadTexture("assets\\Cards\\Paper.png");
        SDL_Texture* S = window.loadTexture("assets\\Cards\\Scissors.png");

        Card rock(Vector2f(394.f, 300.f), R, 128, 96, 2);
        Card paper(Vector2f(544.f, 300.f), P, 128, 96, 2);
        Card scissors(Vector2f(694.f, 300.f), S, 128, 96, 2);

        cardsInHand.push_back(rock);
        cardsInHand.push_back(paper);
        cardsInHand.push_back(scissors);
        cardsInHand.push_back(rock);
        cardsInHand.push_back(paper);
        cardsInHand.push_back(paper);
    }

    while (running) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            default:
                break;
            }
        }
        for (Card& C : cardsInHand) {
            if (C.isMouseOver(mouseX, mouseY) && C.getScale() < 2.25) {
                if (hasFront == false) {
                    C.setFront();
                    hasFront = true;
                }
                if(C.isFront())
                    C.changeScale(C.getScale() + .01);
            }
            else if (!C.isMouseOver(mouseX, mouseY) && C.getScale() > 2) {
                C.changeScale(C.getScale() - .01);
                if (C.isFront()) {
                    C.notFront();
                    hasFront = false;
                }
            }
        }
        bool isEven = false();
        int cardsPerSide = 0;
        if (cardsInHand.size() % 2 == 0) {
            cardsPerSide = cardsInHand.size() / 2;
            int i = 0 - cardsPerSide;
            int center = 640 - 96;
            for (Card& C : cardsInHand) {
                if(!C.isUnder()) {
                    C.changePOS(center + (96 * i), C.getY());
                    i++;
                }
            }
        }
        else {
            int middleCard = (cardsInHand.size() / 2) + 1;
            cardsPerSide = cardsInHand.size() / 2;
            int i = 0 - cardsPerSide;
            int center = 640 - 96;
            for (Card& C : cardsInHand) {
                if(!C.isUnder()) {
                    if (i != 0)
                        C.changePOS(center + (96 * i), C.getY());
                    else if (i == 0)
                        C.changePOS(center, C.getY());
                    i++;
                }
            }
        }
        int counta = 0;
        for (Card C : cardsInHand) {
            int countb = 0;
            if (C.isFront()) {
                for (Card& CC : cardsInHand) {
                    if ((CC.getX() + (96 * CC.getScale())) > C.getX() && counta != countb) {
                        CC.changePOS((CC.getX() - 1), CC.getY());
                        std::cout << "Overlapped " << std::endl;
                        //CC.setUnder();
                    }
                    else {
                        //CC.notUnder();
                    }
                    countb++;
                }
            }
            counta++;
        }
        window.clear();
        window.render(RPSScreen);
        int pos = 0;
        int front = -1;
        for (Card& C : cardsInHand) {
            if (C.isFront())
                front = pos;
            else
                window.render(C);
            pos++;
        }
        if(front != -1)
            window.render(cardsInHand.at(front));
        window.display();
    }
    window.clear();
}