Why and How to Use Pseudocode
=============================

Why use pseudocode?
-------------------
Pseudocode may sound like a generic concept, but you can think of it as an outline of your code. Just like an outline of an essay/research paper you may start out with a simple outline (first example). You also need to consider the flow of information, and move paragraphs around to create the best story (second example). As the essay development continues your outline fills in, and you ultimately end up with a just a few points of concern (third example). Eventually everything comes together, and you have a complete essay (see the fully working program).


What are some advantages of pseudocode?

  1. Explain your code to non-programmers
  2. Use it to get comments/suggestions from other programmers
  3. Use it to determine the best logic for your code
  4. Use it as a way of determining objects in your code (help with OOP)       
  	http://en.wikipedia.org/wiki/Object-oriented_programming
  5. Your pseudocode can help you breakdown what to code first and the tests to build for (TDD)
  	http://en.wikipedia.org/wiki/Test-driven_development


Although there are no real rules for pseudocode I will give a couple basic rules I use for each pseudocode example. Our example will be of a relatively simple neuronal circuit model.

Background
-------------------------------------------
In order to understand exactly what the program should ultimately do, we should first discuss some basic properties of neurons, and how they influence each other's activity.

A neuron is defined as an electrically excitable cell that can process and transmit information through electrical or chemical signals. The membrane of the neuron contains specialized proteins
that generate differences in ion concentrations between the external and internal parts of the neuron. This imbalance in ion concentrations between the external and internal parts of the neuron
leads to a charge difference across the membrane called the membrane potential. When the neuron is at rest, i.e. not receiving or transmitting signals, the membrane potential is negative. The neuron
becomes excited when the membrane potential becomes less negative. Neurons tap in to the energy stored in the ion concentration gradients in order to send electrical pulses to neighboring cells, thereby
transmitting information from one cell to another. A single neuron can receive input from thousands of other neurons, and in turn output information onto thousands of other cells. For the purposes
of this model, we focus on local connections between 2 neurons.

Neurons form specialized connections called synapses which allow them to receive and send information. Synapses are said to be either excitatory or inhibitory depending on how it influences
the activity of the receiving (or postsynaptic) neuron. At excitatory synapses, the postsynaptic neuron is excited by the release of excitatory chemicals (or neurotransmitters) from the presynaptic neuron. When the
excitatory neurotransmitter, glutamate for example, is released from the presynaptic neuron into the synapse, it will bind to glutamate receptor proteins, AMPA receptors for example, on the postsynaptic neuron and allow positive ions to
rush into the neuron. This sudden influx of positive ions will cause the membrane potential to become more positive thereby exciting the cell. At inhibitory synapses, the postsynaptic neuron will become
inhibited by the release of inhibitory neurotransmitters (i.e. GABA) by the presynaptic neuron. The inhibitory neurotransmitter GABA will cross the synapse and bind to GABA receptors on the postsynaptic
neuron resulting in the influx of negatively charged ions. This influx of negatively charged ions will make the membrane potential more negative and prevent the neuron from sending electrical signals.
Below is a cartoon showing the synaptic connection between two neurons:

![Output sample](https://github.com/ogonz007/neuron/blob/master/synapse.gif)


Based on the brief description of some neuronal properties, we will generate code that models a small network of two neurons. Neuron 1 will receive a brief excitatory sine wave stimulus.
Neuron 1 will then send an electrical pulse to Neuron 2. This signal will result in the excitation of Neuron 2 which will then send a signal back to Neuron 1. In this sense, the two neurons will form
recurrent connections with each other. A cartoon representation of the small neural circuit is shown below:

![Output sample](https://github.com/ogonz007/neuron/blob/master/2neuronCartoon_woEqns.gif)

With this basic understanding of neuron properties, we can now begin constructing pseudocode which will help us transition from biological facts to a model of neuronal interaction.

Three different types of pseudocode
-------------------------------------------
### 1. Write your code out in your written/verbal language

Strengths of this kind of pseudocode:

  1. This is great for communicating with non-programmers
  2. It will allow you to think through your program and come up with your initial logic
  3. When things are separated by lines it may indicate they should be an object (OOP)
  4. Being separated by a line may also mean you should build a test for it and then create it (TDD)


Rules:

  1. Write so it is easy for others to understand
  2. Write so you can walk away from this project, pick it up another day and be able to understand your plan
  3. Write related ideas without blank line between them, put blank lines between ideas that are less/not related
  4. Start your pseudocode with what your code is supposed to accomplish
  5. Indent if using flow control (loops, if/else...)


```
What is my code supposed to accomplish?
The code needs to create two neurons. One neuron will receive a sine wave as a stimulating input for 
a certain amount of time. The neurons will have recursive excitatory synapses... meaning: 
sin_wave -> neuron1 <-> neuron2 (see Background section for image).

define how long we want to calculate the neurons' responses (total iterations)

define regular spiking neurons
    initialize neurons
    
define connectivity between neurons
define AMPA synapses

while time is less than the total time, we want to calculate the neurons' responses
    calculate the synaptic current at each active synapse
    calculate the state of each cell
        if this cell type receives external input
            add external input (sin wave) to synaptic activity then calculate activity of the cell
        else
            calculate activity of the cell given its synaptic activity
            
    print external input and neuronal activity to files
```
Now that we have a general idea of what needs to occur in our program and in what order it should occur, we should now consider how the information should flow in the
program. In the next example we will show how to create a flowchart of the program to help you think through the logic (if, while, ...) of the program.

### 2. Flowchart pseudocode

Strengths of this kind of pseudocode:

  1. This is particularly useful if you are working in a brownfield program, where you need to consider how your additions to the program will co-exist with previous code (http://en.wikipedia.org/wiki/Brownfield_(software_development))
  2. Makes you think through the logical flow of your program
  3. Can help you see where using a function may be naturally beneficial to the architecture of your program


Rules:

  1. Separate different components by using different symbols to indicate:
  
    * the beginning and end of the program
    * input and output of the program
    * assignment of a value to a variable, constant, or parameter
    * a point where a decision is made
    * beginning of a repetition
    * algorithms specified outside of the program
    * direction and order of execution (I prefer arrows for this)
  

![Output sample](https://github.com/ogonz007/neuron/blob/master/neuronFlowChart.gif)

Up to this point, we have had a good idea of what the program should do, in what order certain operations should be done, and have visualized the flow of information through
the program. We will use information from the previous pseudocode examples to generate code based pseudocode for 
one function of the final working program.

### 3. Code based pseudocode

Strengths of this kind of pseudocode:

  1. Communicating with other programmers to get opinions/suggestions
  2. Allows you to think through difficult algorithms across multiple days without blindly coding
  3. Makes for an easy transition to complete code


Rules:

  1. Write so it is easy for other programmers to understand
  2. Write so you can walk away from this project, pick it up another day and be able to understand your plan
  3. This is almost complete code, so use all or almost all the formatting you normally would

```C++
void fun(int t, RS (&cellType1)[ncellType1], RS (&cellType2)[ncellType2], bool (&C_CT1CT2)[nCT1][nCT2], 
  bool (&C_CT2CT1)[nCT1][nCT2], AMPAmap1 (&ampa_CT1CT2)[nCT1][nCT2],AMPAmap1 (&ampa_CT2CT1)[nCT1][nCT2])
{
	for(i = 0; i < ncellType1; i++){
		IsynCT1CT2 = 0.0; //synaptic current from cell1 -> cell2
		IsynCT2CT1 = 0.0; //synaptic current from cell2 -> cell1
		for(j = 0; j < ncellType2; j++){
			If(connection is from cell1 to cell2){
				calculate ampa_strengthCT1CT2;
				IsynCT1CT2 += ampa_strenghtCT1CT2;
			}
			If(connection is from cell2 to cell1){
				calculate ampa_strengthCT2CT1;
				IsynCT2CT1 += ampa_strengthCT2CT1;
			}
		}
	}
	for(i = 0; i < ncellType1; i++){
		cellType1[i] = calculate_voltageResponse(externalInput(t,0) + IsynCT1CT2[i]);
		cellType2[i] = calculate_voltageResponse(IsynCT2CT1[i]);
	}
}

```

Here, we have provided an example of code based pseudocode for one of the functions in the fully working program below. This type of pseudocode should be generated for particularly difficult algorithms or functions. You will use this code based pseudocode to easily transfer to code, you can track how we did that in the final code presented next.

Our Final Code
--------------

When looking at this code consider how we used our pseudocode to develop it and some of the weaknesses it still has.

  * How would this code break if we had more than one cell for each cell type?
  * How would this code break if we had different numbers of cell type 1 and cell type 2?
  * Based on our pseudocode how could we have broken up our function `fun()` even more?

```C++
void fun(int t, RS (&cellType1)[ncellType1], RS (&cellType2)[ncellType2], bool (&C_CT1CT2)[nCT1][nCT2], 
  bool (&C_CT2CT1)[nCT1][nCT2], AMPAmap1 (&ampa_CT1CT2)[nCT1][nCT2],AMPAmap1 (&ampa_CT2CT1)[nCT1][nCT2]){

  unsigned i, j;
  double IsynCT1CT2[ncellType1];
  double IsynCT2CT1[ncellType2];

  // calculating synaptic current form one cell to another---------------------------------
  for(i = 0; i < ncellType1; i++){
    IsynCT1CT2[i] = 0.0;
    IsynCT2CT1[i] = 0.0;
    for(j = 0; j < ncellType2; j++){
        if(C_CT1CT2[i][j] == true){
                ampa_CT1CT2[i][j].calc(g_ampa_CT1CT2/cellType1[i].S_CX_DEND, cellType1[i].x, 
                  cellType2[j].spike);
                IsynCT1CT2[i] += ampa_CT1CT2[i][j].I;
        }
        if(C_CT2CT1[j][i] == true){
                ampa_CT2CT1[j][i].calc(g_ampa_CT2CT1/cellType2[j].S_CX_DEND, cellType2[j].x, 
                  cellType1[i].spike);
                IsynCT2CT1[j] += ampa_CT2CT1[j][i].I;
        }
    } //for j
  }//for i 

  //----calculate the state of all cells at the next iteration based on synaptic input-------
  for(i = 0; i < ncellType1; i++){
     cellType1[i].calc((g_ampa_CT1DCpulse*apply_DC_pulse(t,0))+IsynCT1CT2[i]);
     cellType2[i].calc(IsynCT2CT1[i]);
  }
}

```
For the full neuron code, see the file simple_model.cxx. To run the model yourself download simple_model.cxx and the Makefile, then use make run to compile and run the executable.

Our Code Output plotted in MATLAB and made into a gif
-----------------------------------------------------
Here is an example of the data generated by the modeled neurons:

![Output sample](https://github.com/ogonz007/neuron/blob/master/Neuron.gif)



