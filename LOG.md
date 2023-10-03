## What this is

some stories in my CS education - artificial intelligence to be precise
    
Hopefully you'll find them interesting.

## Let me Make a Introduction

I am a college student majoring in Artificial Intelligence and a member in the world of computer science.

### Programming Languages I'm Using

I am a shrewd C\C++ programmer and knows a little bit about Python, Java and MATLAB and Golang.

### What I'm interested in

I'm currently interestd in virtual machines, artificial neuro networks and DataBase systems.

#### virtual machines

Some classmates thought it a pity that I didn't choose to major in micro electronics because it is much more challenging and rewarding. And 
on occasion I found myself thinking about why I chose to major in Artificial Intelligence. Was it because my best friend John Zhan also chose it?
Or basic physics lab and fudamental circuit turned me away? I cannot deny that the two are part of the reason, but indeed they're not the determining one.
As my knowlege of computer advances, the answer to the question become clear to me: this major is based on trial, relatively low-cost trial.
When I encounter failure of program, I can debug, compile, and run it again. As for safety and system trials which may disable your operating system, 
you can perfectly do them in a **virtual machine**. If you get an error, remove the virtual machine, download a new one, and run the trial again.
As for electronics, the failure of a trial can be rather expensive. I heard a graduate who designed a chip and spent months building and testing it.
Unfortunately, this design had a fudamental problem and none of the chips he built passed the final test. 
But error is an integral part of life--all the programmers make mistakes, and most of them,including me, make mistakes every day! 
It is such a fortune that these mistakes almost cost nothing with a virtual machine. And perhaps that's why I joined the family of computer science.

#### Artificial Neuro Networks

This is perhaps the basic of most Deep Learning Programs. The motivation of neuro network is intuitive--what can be done by real neuro network can be 
done by artificial network. Based on such conviction, I took the course [Deep Learning Onramp](http://www.mathworks.com) and figured out how to build one 
using MATLAB. But I was not satisfied--the idea that a few fuction calls can automatically train a network sounds like a magic. Still I wanted to train 
one **starting from scratch without any dependencies**. And I made [it](http://github.com/Fudanyrd/BPNet). The perfect tool was certainly C++ for its inherence and dynamic bounds.

Consider there are 3 kinds of Layers in neuro networks:
>**Input Layer**: for drawing input data and pass them down

>**Hidden Layer**: for processing data it receives and pass them down

>**Output Layer**: where you can find the output 
Undoubtedly there should be a base class\(I named it BPBase\) which should have at least adjust_weights(), layerforward() methods. 

My [first successful trained network](https://github.com/Fudanyrd/BPNet/blob/master/fd_max.cpp) was one with 4 layers, 18 neuros which can tell the larger of two inputs. I set max iteration to be 131072\(pretty large indeed\). And here are its test performances:

0.68,0.23: 0.682174 

0.98,0.12: 0.96465

0.23,0.66: 0.664107

0.59,0.12: 0.596418

0.15,0.09: 0.175814

0.24,0.78: 0.777858

0.89,0.94: 0.95322

0.12,0.03: 0.153387

0.2,0.8: 0.801037

0.45,0.05: 0.461347

The network was a success because it seems to have *remembered* the rule of each inputs and its supposed outputs. To make the result more precise, maybe 
adding more Hidden Layers or adding more neuros to current hidden layers may help.

#### DataBase systems

It seems common sense to us that computer network makes it much easier to obtain information you need. I reckon it is because every device is armed with
searching engines like Google, Baidu, etc. I was not satisfied with letting searching engines to do the information-hunting job for me, so when I took 
the summer courses and learnt basic knowledges in Python I started to build my own network crawlers\(a kind of program which can seize the information you need from webpages\).

However, it was not long before I ran into trouble--the first thing a network crawler do is to download seas of information into your own computer and  then process them and extract those you want. So, I had to deal with the problem--how to store and organize large amounts of information without eating up memory simultaneously make it easier for my network crawler to process. That's exactly what DataBase system can do for me.

### My Favorite Quotes

>\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-

> *There are two kinds of beauty in the world*

> *One is the concise but profound algorithms*

> *The other is your broad sincere smile*

> *Upon locating a bug* 

>\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-

## On What Tools to Use

In this part I will tell one stories of my own. Hopefully you'll like it\(If you're also a CS student, you are likely to be familiar with it, though\).

One day I was working on a middle-scale program but it couldn't run upon \"completion\". Of course the next thing I had to do was to read through all the 
`for` loop in case I left out something. At the beginning I was doing carefully but soon I lost patience because of those poorly-organized\[0\] code blocks. Thank God! I eventually *located* a imagined bug. As usual I annotated this code block and rewrited it. I thought God was playing a joke on me because again it failed on OJ. Worse still, I deleted all the annotation when submitting my work to OJ\(which means that I lost my previos version forever\)!! I didn't solve the problem at last. I never deleted any lines of annotation since then.

**It** was when I was learning Python during the summer vacation of my freshman year that I realized my scarce of knowlege in using **tools** such as 
[git](https://git-scm.com/), [vim](https://www.vim.org/), [cmake](http://cmake.org)\[1\] and so on. When I was *eventually* be able
to use them in a shrewd manner, I thought they are worth their developers' efforts\(even though I thought quite the opposite while learning to use them\).
Take Git for example. Git is an **excellent** version control system. Before using git, the most common mistake I committed was "Oh shit! I have just
deleted useful codes!? ". Else I would annotate blockes of my codes when debugging as what I did in the story. However, with Git, I can easily switch to any branches or discard the changes I made. Unfortunately, more often than not, these tools are not easy to learn\(I concede that the interface of Git is even a little ugly\). That is perhaps the **price** you need to pay for a faster and more fluent workflow.

\[0\]: This experiece taught me a lesson: I should have made my codes well-organized, at least readable. 

\[1\]: If you use IDEs\(Integrated Development Environment\) such as Visual Studio, you don't have to write your own CMakeLists.txt, because IDE can do this for you.

>\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-

> *There are two kinds of beauty in the world*

> *One is the concise but profound algorithms*

> *The other is your broad sincere smile*

> *Upon locating a bug* 

>\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-

## On How Many Programming Languages You should Master

The answer is obvious for a famous quote in the world of computer science: *Language are tools. You choose the right language to do the right thing.*
*Since there are no universially perfect tool, there are NO universially perfect language.*

I was intimidated when I learned from [http://csdiy.wiki](http://csdiy.wiki) which is run by a senior from Pecking University that as a CSer\(Computer
Science student\), you should at least master C\\C++\\Python\\Java\\Js\\Go\\Rust\\SQL!!! I couldn't help asking why it takes so many programming languages
to **survive** in the world of computer science.
While learning these programming languages, keep in mind - you should *first* learn how to program, and *next* is to learn programming language.
Is the one who knows the most words the best writer? Is the one who can play the most notes the best musician? Is the one who practice drawing the most 
the best painter? Obviosly, these assertions are rather absurd. But we often pretends that the best programmer are those who knows the most about 
language traits. This view is rediculous for the same reason\[1\]. Learning a language is **easy**, solving a problem is much more **difficult**. 
I have gradually realized that after all, languages are tools. All you need to do is to choose one based on the problem you are working on.

*Below is my feelings of some programming languages*

>C\C++: fast, easy to extend

>Python: easy to get started, newcomer-friendly.

>Java: similar to C\C++, but has an advantage of thread control and net programming.

>MATLAB: a numeric calculation oriented programming language, widely used in machine learning and deep learning\(perhaps it can also help you a little bit to do your linear algebra homework!!\)

\[1\]: It is translated from one of my favorite C++ tutorial--*Ruminations on C++*.

>\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-

> *There are two kinds of beauty in the world*

> *One is the concise but profound algorithms*

> *The other is your broad sincere smile*

> *Upon locating a bug* 

>\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-

## Recursive? Non-recursive with Stack? Non-recursive without Stack?

\-\-\-

*From Now on, try to solve a problem in more than one ways.*

\-\-\-

Recently I met an interesting question: design an recursive | non-recursive using stack | non-recursive without stack to solve Ackerman function.

ack(m, n) = n+1, m==0 | ack(m-1,1), n==0 | ack(m-1,ack(m,n-1)), m*n!=0

### Recursive Solution

quite obvious. Just do as told.

### Non-recursive Solution using Stack

make a little change to your recursive solution, like this:
```
//....snip....
    long v = ack(m,n-1);
    return ack(m-1,v);
```
and draw recursion tree, the answer will come to you.

### Non-recursive Solution without Stack

Well, a hard nut to crack. But you probably won't forgot the iteration algorithm of solving Fibonacchi series.

How you did that? It may look like this:

```

    long Fib(int n){
        long x = 1, y = 1;
        for(int i=0;i!=n;++i){
            x, y = y, x + y; //of course you cannot do this in C\C++.
        }
        return x;
    }

```

The great idea here is that you can **store the value of key variables** and continue the iteration. Now look back at Ackerman's puzzle.

You can store all the ack(m, n) in a 2-dimension array, like this:

`long dat[2][5];`

The first row is obiously {1,2,3,4,5,...}

And according to definition, the second row is: {2,3,4,5, ...}

And the third row: {3,5,7,9, ...}

And the fourth row: {5,11,...} and so on.

Here is a piece of code to do this:

```
long ack(unsigned int m,unsigned int n){
	long* dat = new long[4096], *aux=new long[4096];
	unsigned int i = 0, c=4096;

	/* calculate the first row. */
	for(int i=0;i!=4096;++i){
		aux[i] = i+1;
	}

	/* calculate until reach the last row. */
	for(unsigned int row=0;row!=m;++row){
		i = 0;
		for(unsigned int col = 1;col < 4096;){
			dat[i] = aux[col];
			col = dat[i];
			++i;
		} /* swap the two array: dat and aux.*/
		long* temp = dat; dat = aux; aux = temp;
	}
	return aux[n];
}
```
I should concede this is only a theretical algorithm because doing so requires much memory. Done.

>\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-

> *There are two kinds of beauty in the world*

> *One is the concise but profound algorithms*

> *The other is your broad sincere smile*

> *Upon locating a bug* 

>\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-

## Misused Pointers can be Highly Problematic

When I was working on part of my [cpp datastructure repository](http://github.com/Fudanyrd/cpp_core), I experieced countless bugs caused by pointer. Most of them are because of using destroyed or worse, null pointers.

Here is [an example](https://github.com/Fudanyrd/cpp_core/blob/main/BSTree.h) of this:
```
template <typename _T>
void BSTree<_T>::remove(const _T& value){
	if(this->find(value) == 0) return;
	BSNode<_T>* p=Root, *pr=0, *ppr=0, *q;
	Stack<BSNode<_T>*> path;
	int d, dd = 0;

	while(!path.empty()){
		//skip, not important for this topic.
		//you can find this code blocks from line 269-363.
	}
	Root = pr;
	delete p;
	return;
}

```
If you frequently deal with C pointers, you are likely to notice some risk factors: 
`BSNode<_T>* p=Root, *pr=0, *ppr=0,*q; ` and `delete p;`. They indeed caused some troubles when I tried to add a remove method for my BSTree class\(Binary Sorted tree, actually AVL tree\). pr and ppr are initialized null; q is **NOT** initialized at all! But I shouldn't allocate memory for them because they are simply auxiliary. Since I paid special attention to those uninitialized pointers, So far, so good.

But bug soon came to me as soon as the programme broke from the `while` loop. I spent hours found the bug. The problem was really interesting\(annoying\)and hard to find. While debugging, I focused mainly on the `while` loop, it seemed to be functioning normally. When the function call was over and programme returned to the main function, I soon received a bug report saying that p was a useless pointer, all of its members were invalid! **I deleted the `delete` statement**, It worked nice. Then I realized that the `delete` statement will call the destructor, i.e. I let the destructor to recursively delete all its children nodes!! That's why I met useless pointer reference. 

Luckily the bug was easy to fix. when removed from the tree, I let the node's both children pointer to be all zero so that the destructor won't screw all these up. And you can see the correct remove method on github now.

>\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-

> *There are two kinds of beauty in the world*

> *One is the concise but profound algorithms*

> *The other is your broad sincere smile*

> *Upon locating a bug* 

>\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-