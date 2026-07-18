/*
this is a test for the lib's function
*Note: not a documantary.
       a documantary is found in ./examples/examples.cpp
*/

#include "NN.hpp"

#include <iostream>

using namespace NN;

int main()
{
    Network net;
    // net.import_nn("../src/model.json");

    // // floatvec input = {0.5f, 0.2f, 0.1f, 0.9f}; // random example

    std::vector<floatvec> input = {
        tokenizer("Hello, how are you?"),
        tokenizer("What is your name?"),
        tokenizer("what do you like to order?"),
        tokenizer("what is the meaning off this"),
        tokenizer("My name is Riad"),
        tokenizer("pizza is good"),
        tokenizer("burgers are good"),
        tokenizer("nachos are good"),
    };
    std::vector<floatvec> target = {
        {0.f, 1.f},
        {0.f, 1.f},
        {0.f, 1.f},
        {0.f, 1.f},
        {1.f, 0.f},
        {1.f, 0.f},
        {1.f, 0.f},
        {1.f, 0.f},
    }; // target[i = 0] = not question, target[i = 1] = question

    // Questions
    input.push_back(tokenizer("how are you doing today"));
    input.push_back(tokenizer("what time is it now"));
    input.push_back(tokenizer("can you help me with this"));
    input.push_back(tokenizer("where is the nearest station"));
    input.push_back(tokenizer("why is the sky blue"));
    input.push_back(tokenizer("who is the president"));
    input.push_back(tokenizer("do you like ice cream"));
    input.push_back(tokenizer("is it going to rain"));
    input.push_back(tokenizer("have you seen my keys"));
    input.push_back(tokenizer("will you be there later"));
    input.push_back(tokenizer("could you open the window"));
    input.push_back(tokenizer("may I sit here"));
    input.push_back(tokenizer("should we start the meeting"));
    input.push_back(tokenizer("how much does this cost"));
    input.push_back(tokenizer("where did you go"));
    input.push_back(tokenizer("which one is better"));
    input.push_back(tokenizer("are you hungry"));
    input.push_back(tokenizer("did you finish the task"));
    input.push_back(tokenizer("does he know the truth"));
    input.push_back(tokenizer("can we go home now"));
    input.push_back(tokenizer("what are you thinking about"));
    input.push_back(tokenizer("how do I fix this"));
    input.push_back(tokenizer("is the coffee hot"));
    input.push_back(tokenizer("who won the game"));
    input.push_back(tokenizer("where do you live"));
    input.push_back(tokenizer("why are you laughing"));
    input.push_back(tokenizer("do they have any water"));
    input.push_back(tokenizer("is there a doctor here"));
    input.push_back(tokenizer("what is your favorite color"));
    input.push_back(tokenizer("can you speak louder"));
    input.push_back(tokenizer("how was your weekend"));
    input.push_back(tokenizer("are we there yet"));
    input.push_back(tokenizer("did it work"));
    input.push_back(tokenizer("will they arrive on time"));
    input.push_back(tokenizer("is this the right way"));
    input.push_back(tokenizer("what happened last night"));
    input.push_back(tokenizer("why did you leave"));
    input.push_back(tokenizer("where is the bathroom"));
    input.push_back(tokenizer("who told you that"));
    input.push_back(tokenizer("do you have a pen"));
    input.push_back(tokenizer("can I borrow your phone"));
    input.push_back(tokenizer("is the door locked"));
    input.push_back(tokenizer("how long is the flight"));
    input.push_back(tokenizer("are you busy right now"));
    input.push_back(tokenizer("what is the weather like"));
    input.push_back(tokenizer("did you call me"));
    input.push_back(tokenizer("is he coming to the party"));
    input.push_back(tokenizer("where is my bag"));
    input.push_back(tokenizer("how many people are coming"));
    input.push_back(tokenizer("who is at the door"));

    // Add 50 question targets
    for (int i = 0; i < 50; i++)
        target.push_back({0.f, 1.f});

    // Statements
    input.push_back(tokenizer("it is a sunny day"));
    input.push_back(tokenizer("I am going to work"));
    input.push_back(tokenizer("the cat is sleeping"));
    input.push_back(tokenizer("I love programming in cpp"));
    input.push_back(tokenizer("the book is on the table"));
    input.push_back(tokenizer("water boils at hundred degrees"));
    input.push_back(tokenizer("the train arrives at noon"));
    input.push_back(tokenizer("she is a very talented artist"));
    input.push_back(tokenizer("my favorite food is pasta"));
    input.push_back(tokenizer("they are playing football"));
    input.push_back(tokenizer("this computer is very fast"));
    input.push_back(tokenizer("I forgot my umbrella"));
    input.push_back(tokenizer("the music is too loud"));
    input.push_back(tokenizer("we are learning neural networks"));
    input.push_back(tokenizer("the city is very quiet"));
    input.push_back(tokenizer("he forgot to bring his laptop"));
    input.push_back(tokenizer("today is Monday"));
    input.push_back(tokenizer("birds can fly high"));
    input.push_back(tokenizer("this pizza tastes amazing"));
    input.push_back(tokenizer("the car is out of gas"));
    input.push_back(tokenizer("I have two brothers"));
    input.push_back(tokenizer("she works at a hospital"));
    input.push_back(tokenizer("it is cold outside"));
    input.push_back(tokenizer("the movie starts soon"));
    input.push_back(tokenizer("I need some sleep"));
    input.push_back(tokenizer("the flowers are blooming"));
    input.push_back(tokenizer("coffee gives me energy"));
    input.push_back(tokenizer("he is my best friend"));
    input.push_back(tokenizer("the earth is round"));
    input.push_back(tokenizer("I finished my homework"));
    input.push_back(tokenizer("the ocean is blue"));
    input.push_back(tokenizer("they live in a big house"));
    input.push_back(tokenizer("I like to read books"));
    input.push_back(tokenizer("she is wearing a red dress"));
    input.push_back(tokenizer("the sky is turning dark"));
    input.push_back(tokenizer("my phone is charging"));
    input.push_back(tokenizer("we went to the beach"));
    input.push_back(tokenizer("he has a nice watch"));
    input.push_back(tokenizer("this is a great library"));
    input.push_back(tokenizer("I am feeling happy"));
    input.push_back(tokenizer("the park is full of people"));
    input.push_back(tokenizer("she likes to dance"));
    input.push_back(tokenizer("the soup is delicious"));
    input.push_back(tokenizer("I bought a new shirt"));
    input.push_back(tokenizer("the clock stopped working"));
    input.push_back(tokenizer("it is time to go"));
    input.push_back(tokenizer("the cake is in the oven"));
    input.push_back(tokenizer("they are watching a movie"));
    input.push_back(tokenizer("I am learning something new"));
    input.push_back(tokenizer("the sky looks beautiful"));

    // Add 50 statement targets
    for (int i = 0; i < 50; i++)
        target.push_back({1.f, 0.f});

    net.addLayer(10, actType::ReLU); // *new, old: 4
    net.addLayer(50, actType::ReLU); // *new, old: 3
    net.addLayer(60, actType::ReLU); // *new, old: none
    net.addLayer(2, actType::Sigmoid);

    // floatvec output = net.forward(input);

    // for (float v : output)
    //     std::cout << v << std::endl;

    net.trainLoop(input, target, 1000, 0.001);
    std::cout << "Done!" << std::endl;
    // exit(0);
    std::system("clear");

    // test
    std::string in;

    while (true)
    {
        std::cout << "Enter a sentence (or type quit): ";
        std::getline(std::cin, in);

        if (in == "quit")
            break;

        floatvec inputVec = tokenizer(in);
        floatvec res = net.forward(inputVec);

        if (res.size() < 2)
        {
            std::cout << "invalid output\n";
            continue;
        }

        std::cout << (res[0] > res[1] ? "not question\n" : "question\n");

        std::string correct;
        while (true)
        {
            std::cout << "is this correct? (Y/n): ";
            std::getline(std::cin, correct);

            if (correct == "y" || correct == "n" || correct == "")
                break;
        }

        if (correct == "n")
        {
            std::vector<floatvec> inp = {tokenizer(in)};
            std::vector<floatvec> tar = {floatvec{1.f, 0.f}};
            if (res[0] > res[1])
                tar = {floatvec{0.f, 1.f}};
            net.trainLoop(inp, tar, 200, 0.1);
            // net.backpropegation(floatvec{1.f, 0.f}, 0.3f);
        }
    }

    // net.dump_nn("model.json");

    return 0;
}