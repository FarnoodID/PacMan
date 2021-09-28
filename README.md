# PacMan

It is a simple form of PacMan Game in which the computer can plays it itself after pressing 'c' by going for the first '*' until there is none left. There is a diffrent format for input; as 0 is PacMan, 1 is a free house, * is heart and # is a block.
**To move, use arrow keys.**
There is no ghost in this phase yet.

To know more about the input maps' format, refer to one of the maps and compare it to the output.

## Introduction

The PacMan searches the nearest star and goes for it.
For every move it waits 0.5 second.
The program ends with the last star eaten.

### Code Box 

This PRINTF changes color to blue in dev c/c++

````
printf("\033[1;34m");
````
This IF checks if a scroll key was pressed and if not ch will keep whatever is in it.

```
if (ch == 0xE0)
{
	ch2 = getch();
	switch(ch2)
	{
	case 72: side=8; break;
	case 80: side=2; break;
	case 75: side=4; break;
	case 77: side=6; break;
	default:;
	};
}
```
These three functions use an array to keep queue. 'enqueue' adds to array, 'dequeue' removes from it and 'isEmpty' checks if it is empty. 

```
void enqueue(Queue *q,int a)
{
	q->arr[q->j++] = a;
}
int isEmpty(Queue *q)
{
	return q->i >=  q->j;
}
int dequeue(Queue *q)
{
	return q->arr[q->i++];
}
```
It is implemented to find the nearest heart ('*') in order by using BFS algorithm.
 
## Author

* **ِFarnood**- [FarnoodID](https://github.com/FarnoodID)

## License

This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/FarnoodID/PacMan/blob/master/LICENSE) file for details
