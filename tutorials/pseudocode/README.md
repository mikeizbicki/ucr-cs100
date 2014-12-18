Why and How to Use Pseudocode
=============================

Why use pseudocode?
-------------------
Pseudocode may sound like a generic concept, but you can think of it as an outline of your code. Just like an outline of an essay/research paper you may start out with a simple outline (example one). You also need to consider the flow of information, and move paragraphs around to create the best story (second example). As the essay development continues your outline fills in, and you ultimately end up with a just a few points of concern (third example). Eventually everything comes together, and you have a complete essay (see the functional program).

If you are comfortable writing programs without pseudocode there is one significant advantage to adding pseudocode to your repitoire... It allows you to think through the entire logic of your code and how it interacts with other parts of the program (if you are working in a brownfield environment). This also helps to ensure that if you are using test-driven development (TDD) you already have a strong image of how all the necessary subcomponents are going to come together, making the refactoring component of TDD simple.

What are some advantages of pseudocode?
<ol>
  <li>Explain your code to non-programmers</li>
  <li>Use it to get comments/suggestions from other programmers</li>
  <li>Use it to determine the best logic for your code</li>
  <li>Use it as a way of determining objects in your code (help with OOP)</li>
  <li>Your pseudocode can help you breakdown what to code first and the tests to build for (TDD)</li>
</ol>

Although there are no real rules for pseudocode I will give a couple basic rules I use for each pseudocode example.

Our example will be of a relatively simple neuronal circuit model. If you are interested in neuroscience or would like an explanation of some of the terms we use please read the section at the end titled "Background".

Examples of pseudocode and when to use them
-------------------------------------------
### 1. Write your code out in your written/verbal language

Strengths of this kind of pseudocode:
<ol>
  <li>This is great for communicating with non-programmers</li>
  <li>It will allow you to think through your program and come up with your initial logic</li>
  <li>When things are separated by lines it may indicate they should be an object (OOP)</li>
  <li>Being separated by a line may also mean you should build a test for it and then create it (TDD)</li>
</ol>

Rules:
<ol>
  <li>Write so it is easy for others to understand</li>
  <li>Write so you can walk away from this project, pick it up another day and be able to understand your plan</li>
  <li>Write related ideas without blank line between them, put blank lines between ideas that are less/not related</li>
  <li>Start your pseudocode with what your code is suppose to accomplish</li>
  <li>Indent if using flow control (loops, if/else...)</li>
</ol>

```
What is my code suppose to accomplish?
The code needs to create two neurons. One neuron will receive a sine wave as a stimulating input for a certain amount of time. 
The neurons will have recursive excitatory synapses... meaning: sin_wave -> neuron1 <-> neuron2 (see Background section for image).

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

### 2. Flowchart pseudocode

Strengths of this kind of pseudocode:
<ol>
  <li>This is particularly useful if you are working in a brownfield program, where you need to consider how your additions to the program will co-exist with previous code</li>
  <li>Makes you think through the logical flow of your program</li>
  <li>Can help you see where using a function may be naturally beneficial to the architecture of your program</li>
</ol>

Rules:
<ol>
  <li>Separate different components by using different symbols to indicate:</li>
  <ul>
    <li>the beginning and end of the program</li>
    <li>input and output of the program</li>
    <li>assignment of a value to a variable, constant, or parameter</li>
    <li>a point where a decision is made</li>
    <li>beginning of a repitition</li>
    <li>algorithms specified outside of the program</li>
    <li>direction and order of execution (I prefer arrows for this)</li>
  </ul>
</ol>

![Output sample](https://github.com/ogonz007/neuron/blob/master/neuronFlowChart.gif)


### 3. Code based pseudocode

Strengths of this kind of pseudocode:
<ol>
  <li>Communicating with other programmers to get opinions/suggestions</li>
  <li>Allows you to think through difficult algorithms across multiple days without blindly coding</li>
  <li>Makes for an easy transition to complete code</li>
</ol>

Rules:
<ol>
  <li>Write so it is easy for other programmers to understand</li>
  <li>Write so you can walk away from this project, pick it up another day and be able to understand your plan</li>
  <li>This is almost complete code, so use all or almost all the formatting you normally would</li>
</ol>
```C++
void fun
{
	For(i = 0; i < ncellType1; i++){
		set IsynCT1CT2 to 0.0; //synaptic current from cell1 -> cell2
		set IsynCT2CT1 to 0.0; //synaptic current from cell2 -> cell1
		For(j = 0; j < ncellType2; j++){
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
	For(i = 0; i < ncellType1; i++){
		cellType1[i] = calculate_voltageResponse(externalInput(t,0) + IsynCT1CT2[i]);
		cellType2[i] = calculate_voltageResponse(IsynCT2CT1[i]);
	}
}

```


Our Final Code
--------------

When looking at this code consider how we used our pseudocode to develop it and some of the weaknesses it still has.
<ul>
  <li>How would this code break if we had more than one cell for each cell type?</li>
  <li>How would this code break if we had different numbers of cell type 1 and cell type 2?</li>
</ul>
```C++
#include <stdio.h>
#include <stdlib.h> 
#include <math.h> 
#include <map>

using namespace std;

#define   ncellType1	1   
#define   ncellType2	1
#define   iters		3000
#define	  g_ampa_CT1CT2 0.00068
#define	  g_ampa_CT2CT1 0.00068
#define   g_ampa_CT1DCpulse 1.0
#define   range_left	500
#define   range_right	1000
#define   dc_amplitude	0.1
#define	  a_sin		0.4
#define   sin_bx	0.076
#define	  trial		10

const int trials[trial] = {0,5000,10000,15000,20000,25000,30000,35000,40000,45000};

//-- Regular spiking neuron---------------------------------------
class RS{
  double y, xp, xpp, sigma_n, beta_n;
public:
  double alpha, x;	
  double sigma, sigma_e, beta_e, S_CX_DEND, mu;
  int spike;	

  RS(){ init(); }

  void init(){
    spike=0;
    mu=0.0005;		
    alpha=3.65; 	
    sigma=0.06;	
    sigma_e=1.0;
    beta_e=0.03;
    S_CX_DEND = 165.0e-6;

    //initial conditions
    xpp=-1+sigma;
    xp=-1+sigma;
    x=-1+sigma;
    y= x - alpha/(1-x);
  }
  inline void calc(double);
};

void RS::calc(double I){
  //synaptic input currents
  beta_n = beta_e * I;
  sigma_n = sigma_e * I;

  if (beta_n < -1.0) beta_n = -1.0;
  if (beta_n > 1.0) beta_n = 1.0;

  if(xp <= 0.0) {
    x = alpha / (1.0 - xp) + y +beta_n;
    spike = 0;
  }
  else{
    if(xp <= alpha + y +beta_n && xpp <= 0.0) {
      x = alpha + y + beta_n;
      spike = 1;
    }
    else {
      x = -1;
      spike = 0;
    }
  }

  y = y - mu* (xp +1.0) + mu * sigma + mu * sigma_n;
  xpp = xp;
  xp = x;
}

//---------AMPA synapse class-------------------------------------------
class AMPAmap1 {
  static const double E_AMPA; //reversal potential
  static const double gamma; //conductance decay

public:
  double I, g;  //Current from synapse to soma; synaptic conductance
  AMPAmap1() {
    I=0;
    g=0;
  }
  inline void calc(double, double, int);
};

void AMPAmap1::calc(double g_AMPA, double x_post, int spike) {

  g = gamma * g;
  if(spike) g += g_AMPA;

  I = - g * (x_post - E_AMPA);
}
const double AMPAmap1::E_AMPA = -0.0;
const double AMPAmap1::gamma  =  0.4;

double apply_DC_pulse(int t, double silence){
  for(int i = 0; i < trial; i++)
    if (t>=(range_left+trials[i]) && t<=(range_right+trials[i])) return dc_amplitude + a_sin*sin(t*sin_bx);

  return silence;
}

//-----------function to evaluate the Rhs of all the maps---
template<size_t nCT1, size_t nCT2>
void fun(int t, RS (&cellType1)[ncellType1], RS (&cellType2)[ncellType2], bool (&C_CT1CT2)[nCT1][nCT2], bool (&C_CT2CT1)[nCT1][nCT2], AMPAmap1 (&ampa_CT1CT2)[nCT1][nCT2],AMPAmap1 (&ampa_CT2CT1)[nCT1][nCT2]){

  unsigned i, j;
  double IsynCT1CT2[ncellType1];
  double IsynCT2CT1[ncellType2];

  // calculating synaptic current form one cell to another---------------------------------
  for(i = 0; i < ncellType1; i++){
    IsynCT1CT2[i] = 0.0;
    IsynCT2CT1[i] = 0.0;
    for(j = 0; j < ncellType2; j++){
        if(C_CT1CT2[i][j] == true){
                ampa_CT1CT2[i][j].calc(g_ampa_CT1CT2/cellType1[i].S_CX_DEND, cellType1[i].x, cellType2[j].spike);
                IsynCT1CT2[i] += ampa_CT1CT2[i][j].I;
        }
        if(C_CT2CT1[j][i] == true){
                ampa_CT2CT1[j][i].calc(g_ampa_CT2CT1/cellType2[j].S_CX_DEND, cellType2[j].x, cellType1[i].spike);
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

int main(int argc, char **argv)
{

  int  t,ii,i,j;
  double randNum;

  //-------Neurons-----------------
  RS cellType1[ncellType1];
  RS cellType2[ncellType2];

  //------Connectivity (bool)---------  
  bool C_CT1CT2[ncellType1][ncellType2];
  bool C_CT2CT1[ncellType2][ncellType1];

  //--------Synapses-----------------
  AMPAmap1 ampa_CT1CT2[ncellType1][ncellType2];
  AMPAmap1 ampa_CT2CT1[ncellType2][ncellType1];

  //---initialize connectivity matrix-----
  srand(2);
  for(i=0; i<ncellType1; i++)
    for(j=0; j<ncellType2; j++){
      randNum = 1.0 * rand()/(RAND_MAX + 1.0);

      if(randNum < 2)
        C_CT1CT2[i][j] = true;  // all cells interconnected
        C_CT2CT1[i][j] = true;
    }

  FILE     *fcellType1;
  FILE     *fcellType2;
  FILE     *fwaveInput;

  fcellType1 = fopen("cellType1","w");
  fcellType2 = fopen("cellType2","w");
  fwaveInput = fopen("waveInput","w");

 //-----------Start iteration --------------------
  t = 0;
  while (t < iters){

    //evaluate neuronal activity
    fun(t, cellType1, cellType2, C_CT1CT2, C_CT2CT1, ampa_CT1CT2, ampa_CT2CT1);

    //write dcInput to file
    fprintf(fwaveInput,"%f %f \n",(t+1)*0.6, apply_DC_pulse(t,0));

    //write LH spikes to file
    for (ii = 0; ii < ncellType1; ++ii){
        fprintf(fcellType1,"%f %f \n", (t+1)*0.6, cellType1[ii].x);
        fprintf(fcellType2,"%f %f \n", (t+1)*0.6, cellType2[ii].x);
    }

    ++t;
  }

  fclose(fcellType2);
  fclose(fcellType1);
  fclose(fwaveInput);
  return 0;
} //end main

```
Our Code Output plotted in MATLAB and made into a gif
-----------------------------------------------------
Here is an example of the data generated by the modeled neurons:

![Output sample](https://github.com/ogonz007/neuron/blob/master/Neuron.gif)

Background
-------------------------------------------
A neuron is defined as an electrically excitable cell that can process and transmit information through electrical or chemical signals. The membrane of the neuron contains specialized proteins
that generate differences in ion concentrations between the external and internal parts of the neuron. This imbalance in ion concentrations between the external and internal parts of the neuron
leads to a charge difference across the membrane called the membrane potential. When the neuron is at rest, ie. not receiving or transmitting signals, the membrane potential is negative. The neuron
becomes excited when the membrane potential become less negative. Neurons tap in to the energy stored in the ion concentration gradients in order to send electrical pulses to neighboring cell thereby
transmitting information from one cell to another. A single neuron can receive input from thousands of other neurons, and in turn output information onto thousands of other cells. For the purposes
of this model, we only focus on local connections between 2 neurons.

Neurons form specialized connections called synapses which allow neurons to receive and send information. Synapses are said to be either excitatory or inhibitory depending on how it influences
the activity of the receiving (or postsynaptic) neuron. At excitatory synapses, the postsynaptic neuron is excited by the release of excitatory chemicals (or neurotransmitters). When the
excitatory neurotransmitter, glutamate for example, is released at the synapse, it will bind to glutamate receptor proteins, AMPA receptors for example, on the postsynaptic neuron and allow positive ions to
rush into the neuron. This sudden influx of positive ions will cause the membrane potential to become more positive thereby exciting the cell. At inhibitory synapses, the postsynaptic neuron will become
inhibitied by the release of inhibitory neurotransmitters (ie. GABA) by the presynaptic neuron. The inhibitory neurotransmitter GABA will cross the synapse and bind to GABA receptors on the postsynatpic
neuron resulting in the influx of negativly charged ions. This influx of negatively charged ions will make the membrane potential more negative and prevent the neuron from sending electrical signals.
Below is a cartoon showing the synaptic connection between two neurons:

![Output sample](https://github.com/ogonz007/neuron/blob/master/synapse.gif)


Based on the breif description of some of the properties of a neuron, we generated some code that models a small network of two neurons. Neuron 1 receives a breif excitatory sine wave stimulus.
Neuron 1 then sends an electrical pulse to Neuron 2. This signal results in the excitation of Neuron 2 which then sends a signal back to Neuron 1. In this sense, the two neurons are forming
recurrent connections with each other. A cartoon representation of the small neural circuit is shown below:

![Output sample](https://github.com/ogonz007/neuron/blob/master/2neuronCartoon_woEqns.gif)
