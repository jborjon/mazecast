# Mazecast

## The Game

Mazecast is simple: You are thrown into a randomly generated 3D maze—likely the only one exactly like it ever—and you need to get out.

## Background

Programming a first-person-perspective ray caster has been a dream of mine since *Doom* was just under a decade old and I was just over a decade old. I suppose I'm enamored with the idea of being like those early FPS pioneers who wrote their own engines wielding the C programming language with nothing but their bare hands.

I'm no longer that teenage boy who loved the pixelated violence of the mid-90s; I'm more of a pacifist these days. But the fascination with creating an explorable world out of lines of code is as strong as ever.

So I'm using C and nothing else—not for the game itself, anyway. C99, to be specific. That standard's old enough to have existed in the 90s (the period I'm trying to relive) but modern enough to be still widely supported. And to not force me to declare counters outside of `for` loops:

```c
int i;  // why waste a line, C89 style?
for (i = 0; i < 10; ++i)
    ;
```

My aim is to create a simple game that forces me to dive into game programming patterns while allowing me the satisfaction of allocating my own memory, dereferencing my own pointers, and creating my own segfaults.

## Dedication

The world wouldn't be the same today without [Dennis Ritchie](https://en.wikipedia.org/wiki/Dennis_Ritchie) and the other pioneers who made so many technologies, including C, possible. We are all beneficiaries of their work, and this is to their health. You'll live on forever, dmr!
