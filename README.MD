Welcome to mferaoun's && chrleroy's implementaiton of 42 Minishell.

For swagg purpose, we'll refer to it as Minislay throughout this git repo's
content.

Before introducing the subject and our approach, I'd like to introduce the 2
aspiring coding rockstars who wrote this mint code.

Shoutout to Melissa, one of the smartest people I've met so far. Her ability to
tackle complex topic and thei intrications was a key factor of this project's 
sucess. 
I also want to praise her reliability and ability to communicate clearly about 
issues && successes.

..

We've known each other for a year now, and already had the opportunity to work
together ont RUSH00 during our picsine. As it was a delightfull experience, we
decided to tackle together the first group project of 42's common core.

Before getting into the code, we delved into documentation and both completed
pipex project && its bonuses. We'd advise you to do the same as it will test
your ability to reproduce bash posix's behaviour && help you implement a modular
design in your minishell implementation.
Regarding design, we've both been trying to implement clean code principles in 
our programs so far. We think it's a critical part of this project, and 
identified it as one of its main pedagogic's purposes. As we decided to spend at
most 6 weeks on this project, we were convinced that spending time on design
would pay non refactoring dividends down the road.
Also, we aimed at making it scalable in case we'd have enough time left to 
tackle bonuses.

Regarding the parsing, we chose to implement a tree structure. We build the tree
using the following method:

	1.	We get an user input that we read from STDIN and store it as is.

	2.	We perform a space trim || addition outside closed "" && ''.
	3.	We identify grammar elements within the string.

	4.	We create a node for each grammar element && append it within a linked
		list that get passed to the execution part.

	5.	Each grammar node contains a pointer to the first command that gets
		executed within the grammar block. This pointer leads to a linked list
		containing all the commands to be executed within the block.

Examples:

	User input		-> 		<< yay grep    'pommes ' | wc -l > test.txt < cat 
	Parsed input	-> 		<< yay grep 'pommes' | wc -l > test.txt < cat

	Grammar			->		<< yay	
					->		|
					->		> test.txt
					->		< test.txt
	
	Commands		->		grep 'pommes'
					->		wc -l
					->		cat

Note that this example contains valid input. Let's now see how we assessed the
validity of the user's input.

	1.	Redirewctions:

		In bash posix, redirections have a priority over the rest of the input.


		->	< redirections

			We check 

		->	> redirections

		-> << && >> redirections

Regarding the execution, we chose to

Thanks for reading this long rant, we hope you enjoyed our code !
