# A solitare game that i wrote in plain C and OpenGL

## Description
> I wrote this project over the coarse of about a week just as something to get me more familiar with C and I enjoyed writing it so im making it into a more long term project

## Current Features
> - Card rendering <br />
> - Basic board rendering <br />
> - The base solitare rules <br />

## Future updates needed
> - Improved rendering engine <br />
>> New rendering features <br />
>> - Framebuffers <br />
>> - Batched rendering <br />
>> - UI Engine <br />
>> - Text rendering <br />
>> - Maybe vulkan (prob not i just kinda want to try it out) <br />
>>
>> Fix older rendering freatures like <br />
>> - Revamp the meshing system
>> - New shader loader using siron files
> - Improved board rendering <br />
>> Right now the board rendering is very basic and it just draws and image so i have a system planned that will read the data it needs and draw it out to an OpenGL framebuffer at the start of the game that can be drawn every frame <br />

## Optimizations plans
> - cards that are not visible being rendererd <br />
> - game board being redrawn every frame when you can go whole minutes without moving something <br />
> - rework a lot of the card manager script as it is kinda buggy and patchworked together

## Futures plans that could be cool
> More boards <br />