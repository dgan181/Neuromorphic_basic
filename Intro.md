Introduction
============

The desire to build fast and efficient computers has fueled years of research in computing and the Von Neumann architecture, describe in figure [fig:vonne], has become a staple to meet this end. In this architecture, there is a clear line drawn between the processing unit and the memory unit. For a process to take place, information is retrieved from or stored in the memory unit. A major bottleneck to processing speed here is the channel between the memory and processing unit. The efficiency and processing speeds of computers are tuned by dimensional scaling of the transistors that build them up. However, with the transistors approaching their physical limits (Moore’s law ), scientists are recognising a need to shift to an alternate paradigm. This is especially necessary for deep learning tasks that make use of immense neural networks for the purpose of classification and recognition, where power consumption is very high on conventional hardware .

![Von Neumann architecture](Vonneuman.png "fig:") [fig:vonne]

Neuromorphic computing is an alternate approach to computing, where the architecture tries to mimic the structure and function of the human brain. In late 1980s, the term *neuromorphic* was coined to mean organisation of silicon based analog circuits that behave like biological networks of neurons. In recent times, the term has come to be associated with the implementation of neural networks on non-Von Neumann type architecture.

Similar to the vast inter-connections of neuron in the human brain, neuromorphic processors are comprised of densely inter-connected simple analog components. Their organisation grants them inherent parallelism which is a desirable feature for superior computing speeds. Unlike traditional computers, the memory and processing units are co-located which allows these processors to overcome the Von Neumann bottleneck. The primary motivation behind the new paradigm is lower power consumption, this influences the choice of analog components used in a processor as well as algorithmic design that is implemented. Owing to its similarity with the brain, this architecture is naturally more suited for cognition tasks than conventional architecture.

The following sections introduce the biological units that make up the human brain and their analog counterparts. Spiking neural networks are also briefly discussed. The discussions in this chapter follow from

 Neurons and synapses 
----------------------

Neurons are the fundamental processing unit of the central nervous systems. They are biological cells that can form a dense and intricate networks of several kilometers packed into a cubic centimeter. Though there are a variety of neurons present in the brain, for the purpose of neuromorphic computation we are interested only in ideal spiking neurons, since these are the only kind that take part in spike-based information exchange and processing . The input and outputs to and from a spiking neuron are in the form of electrical pulses called action potentials or spikes. The profile of the action potential is irrelevant to information transfer; information is carried in the number and timing of these spikes. A structure of the spiking neuron, shown in figure [fig:bioneuron], can be divided into three parts: the dendrites, the soma and the axon. The dendrites function as input channels bringing in signals from other neurons. The soma behaves as the processing unit of the cell, *integrating* or summing up the signal it receives. The axon acts as output channels to other neurons. The generation of a pulse in a neuron depends on the voltage inside and outside the cell membrane of the soma and the axon. These voltages are governed by Na\(^{+}\) and K\(^+\) channels in the cell that open or close depending on the concentration in the cell. When the membrane potential, the difference between the voltage outside and inside the membrane, crosses a given threshold, a spike is generated. A junction between the dendrites and an axon of two neurons is referred to as a synapse. In literature, an input neuron is typically referred to as a *pre-synaptic* neuron and output neuron as the *post-synaptic* neuron. This terminology shall be used here onward.

![Structure of a biological Neuron](Neuron.png "fig:") [fig:bioneuron]

The most common type of junction between neurons is a chemical synapse, where the axon of the pre-synaptic neuron and the dendrites of the post-synaptic neurons are very closely spaced, leaving a tiny gap between them. This gap is called a synaptic cleft, shown in figure [fig:syn]. At the conception of a pre-synaptic spike, a complex chain of bio-chemical reactions take place at the synapse that results in the release of certain chemicals called neurotransmitters from the the pre-synaptic neuron into the synaptic cleft. On the post-synaptic side, the transmitters are received by special receptors that direct the opening of the aforementioned ion channels and eventually lead to spiking of the neuron. The ability of a post-neuron to fire is greatly dependent on the properties of the synapses that links it to pre-neurons. The synaptic weight determines how much of the signal is allowed to pass through to the post-synaptic neuron.

![Synapse and synaptic cleft](Synapticcleft.png "fig:") [fig:syn]

Additionally, synapses can either be excitatory or inhibitory in nature. The function of an excitatory synapse is to increase the membrane potential of the post-synaptic neuron while that of an inhibitory synapse is to decrease it. Biologically, there are many factors that determine whether a synapse behaves as an excitatory or inhibitory synapse. These include: the type of neurotransmitters that are channeled, the type of receptors that receive these chemicals as well as the concentration of these chemicals. It is possible for a synapse to switch its function depending on these factors. It has been observed that excitatory synapses are always greater in number than inhibitory synapses .

Mathematically, in a biological network, the activity of a post-synaptic neuron, ``S_{j}`` is given as

```math
\begin{aligned}
S_{j}(t + 1) \propto h \Big(\sum_{i} w_{ij} S_{i}(t) \Big) \:,\end{aligned}
```
where \(w_{ij}\) signifies the weight of the synapse and \(h\) is an arbitrary function. The weight of a synapse indicates its behaviour:

\[\begin{aligned}
w_{ij} = \left \{ \begin{matrix}
+ve & \qquad& \text{excitatory} \\
-ve & \qquad& \text{inhibitory}\\
0 & \qquad& \text{inactive or absent} \:\:.\end{matrix} \right.\end{aligned}\]

In practice, neurons can be modelled by a set of nonlinear differential equations that describe how the action potentials are propagated. Hodgkin and Huxley proposed a neuron model that accurately predicted the shape of action potentials generated by a neuron. This gave exceptional insight into the electrical events underlying the action potential. The equations they proposed describe the dynamics of the various ionic channels and leakage channels that contribute to the membrane potential. Inspired by their formulation, simpler models have since been proposed that allow for faster and more efficient simulation of neuronal dynamics. These include models such as the Izhikevich model , the leaky integrate-and-fire (LIF) model and the FitzHugh-Nagumo model . In this work, the leaky integrate-and-fire model has been used for its simplicity in computer simulation and hardware modelling. It is modelled as a resistance, battery and capacitor in parallel with a pathway for an input current as shown in figure [fig:LIF]. When the cell membrane receives a current, the charge it receives with it is stored within the membrane and the membrane potential rises. A capacitor is employed to replicate this behaviour. To account for charge leakage in the cell membrane over time, a resistance is defined. When the input signal ceases, the cell membrane drops down to a resting potential characterised by the battery in the circuit. Formally, the injected current \(I(t)\) at a time \(t\) can be written as:

\[\begin{aligned}
I(t) = \frac{u(t) - u_r}{R} + C \frac{du}{dt} \:,\end{aligned}\]

where \(u(t)\) is the time dependent potential across the circuit, \(R\) and \(C\) are the resistance and capacitance in the circuit as shown in fig [fig:LIF] . The term, \(u(t)\) corresponds to the membrane potential of the circuit. \(u_r\) is the voltage across the battery in the circuit. The equation can be rewritten as:

\[\begin{aligned}
RC\frac{du}{dt} &= -(u(t) - u_r) + RI(t) \\
\tau_m\frac{du}{dt} &= -(u(t) - u_r) + RI(t)\:,\end{aligned}\]

![Leaky integrate-and-fire circuit model](Lif.png "fig:") [fig:LIF]

where \(\tau_m = RC\) is called the time constant of the decay. \(u_r\) behaves like resting potential, i.e. the membrane potential assumes the value of \(u(r)\) when there is no stimulus. The neuron *spikes* when the membrane potential crosses a specified threshold voltage. Immediately after a spike, the neuron briefly enters a *refractory period* where it does not respond to any external inputs. The spiking of such a neuron is displayed in fig [fig:LIF<sub>f</sub>i]. The threshold voltage and refractory period are not explicitly present in the equations; they are specified separately in hardware, where these parameters can be introduced by the addition of capacitors and transistors. In literature, models for LIF neurons proposed that are based on floating-gate integrator circuits .

![image](lif_graph.png) [fig:LIF<sub>f</sub>i]

Neural Networks
===============

Based on the neuronal functions, neural networks are categorised into three generations , shown in figure [fig:gen]. The earliest generation refers to as McCulloch Pitts neurons that function based on a thresholding operation. A neuron, called a linear threshold unit (LTU), gives a binary ’1’ if the weighted sum of all the inputs is above a certain threshold and ’0’ if it is not. They are also called perceptrons. In the second generation of neural networks, the processing of inputs at a neuron is based on an *activation function*. In contrast to the first generation, these allow for a continuous set of possible output values. An example of an activation function is the sigmoid function. The most important feature of the second generation is the compatibility of learning algorithms that rely on gradient descent and back-propagation. Modern deep learning networks are based on the second generation. With great advancement in field of neuroscience, a third generation of spiking neural networks (SNNs) have emerged that show great promise on the efficiency front. These networks use spiking neurons similar to the ones mentioned in the previous section. Information is exchanged through spikes which can essentially be construed as binary signals. The distinction between the third generation and the previous generation of networks lies in how information is encoded. The former utilise the amplitude of the signals while the latter focuses more on the timing of the signals. A neuron in an SNN is active only when it is receiving or emitting signals. The neuron does not consume any power while it is “silent”. This make them more energy efficient in comparison to the previous generations.

<span>
 </span> [fig:gen]

Spiking neural networks are of three kinds, topologically [fig:topo]: (i) feed-forward; (ii) recurrent or (iii) hybrid (a combination of feed forward and recurrent). In feed-forward networks, information flows downstream or in just one direction. The networks are comprised of layers of neurons stacked one after the other with an input layer at one end and an output layer at the other end. Such networks are suitable for low-level sensory systems such as vision. Therefore, they can be used for tasks involving pattern recognition and classification. Recurrent neural networks consist of neurons or populations of neurons that interact through feedback connections. Such networks demonstrate dynamic temporal behaviour. In the human brain, it is believed that such networks play a role in the formation of associative memory and complex decision making. These networks are much harder to train than feed-forward networks. Hybrid networks are a composition of networks that are feed forward and those that are recurrent. Reservoir computing is a widely studied concept that make use of hybrid networks.

 [fig:topo]

The following section briefly discusses some fundamental learning algorithms for SNNs.

Learning in spiking neural networks
===================================

A synapse in a network of neurons is categorised by its weight. Synapses in the human brain can change their weights in response to the spiking of pre-synaptic and post-synaptic neurons. The ability to change and retain their synaptic strength is called synaptic *plasticity*. In the context of neural networks, the term *learning* refers to the determining the weights for specific task. A learning rule is a mathematically exact formulation of how the weight changes. If over time, the synaptic strength is continuously increased, it is called *long term potentiation* or LTP for short. On the other hand, if the synaptic weight decreases persistently, it is referred to as *long term depression* or LTD .

The algorithms described below are ’unsupervised’ learning rules, meaning learning takes place through no additional factors other than the inputs that are fed into the network.

In 1949, Hebb conjectured that if two neuron were causally related in their spiking, then the synaptic connection between them is strengthened . He theorised such a rule would help stabilise neuronal activity and result in associated firings that shows some semblance to learning. Hebb’s idea was further extended to include depression when neuron do not show direct causal correlation. The above statement is often summarised as *\`\` neurons that fire together, wire together"*.

The change in weight of a given synapse depends only on features local to that synapse such as its weight \(w_{ij} \)and the activities of the pre-synaptic neuron, \(v_i\) and post-synaptic neuron, \(v_j\). Keeping this in mind, we can write down a general equation for \(w_{ij}\)

\[\begin{aligned}
\label{eq:hebb}
\frac{d w_{ij}}{ dt} = c_1(w) v_i + c_2(w) v_j + c_3(w) v_i^2 + c_4(w) v_j^2 + c_5(w) v_iv_j + c_6(w) + \mathcal{O}(v^3)\:. \end{aligned}\]

The coefficients in the equation above can be adjusted in accordance to our learning rule. For example, we can design a rule that depends on the firing rates of the neurons. The weight should be updated only when there is post-synaptic firing. Secondly, when the pre-synaptic firing rate is above a threshold, potentation should occur, otherwise depression takes place. These properties are accommodated in the following equation,

\[\begin{aligned}
\frac{d w_{ij}}{ dt} = c_o v_j (v_i - \theta(w_{ij})) \:, \end{aligned}\]

where \(v_i\) and \(v_j\) are the average firing rates measured in a specified time interval and \(\theta\) signifies the pre-synaptic firing threshold. This type of plasticity, that is based on the rate of spiking, is also called *spike rate dependent plasticity* or SRDP in short.

A Hebbian rule can also be described based on the exact firing times of the neuron instead of their rates. The simplest such rule is the *pair-based spike dependent plasticity* rule. Let \(t_{pre}\) be the time of firing of a pre-synaptic neuron and \(t_{post}\) be the time of firing of a post-synaptic neuron. The update rule is given by the difference \( \Delta t \) between the firing times of pre and post-neurons i.e \(\Delta t = t_{post} - t_{pre}\). Formally the rule can be written down as:

\[\begin{aligned}
\Delta w = \begin{cases} + |w_+(\Delta t)| &\qquad \Delta t > 0 \\ - |w_- (\Delta t)| &\qquad \Delta t < 0\end{cases} \:.\end{aligned}\]

In the above equation \(w_+\) and \(w_-\) are arbitrary functions of \(\Delta t\). The rule imports that when a post-firing is followed by a pre-firing, the firings are causally related or \(\Delta t > 0\), hence the synapse experiences potentiation. Similarly, when a post-firing is preceded by a pre-firing, the firings are not causally related or \(\Delta t < 0\) resulting in a depression. It is important to note that an update is in effect only when both the pre and post-neurons fire. A common choice for the functions \(w_{+} \) and \(w_{-}\) is

\[\begin{aligned}
w_{+} &= A_+(w) \exp( - \Delta t / \tau_+) \\
w_{+} &= A_-(w) \exp(  \Delta t / \tau_-) \:,\end{aligned}\]

where \(A_+\) and \(A_-\) are weight dependent function, \(\tau_ +\) and \(\tau_-\) are decay time constants.

![image](stdp_trad.png)

For completeness, the rule can be expressed in the form of eq. , if we introduce activities \(S_{i}\) and \(S_j\) for pre-synaptic and post-synaptic neurons,

\[\begin{aligned}
S_{i} &= \sum_{f} \delta(t - t^{f}_{i}) \\
S_{j} &= \sum_{f} \delta(t - t^{f}_{j}) \:,\end{aligned}\]

with \(t_{i}\) and \(t_j\) indicating the time of firing and \(f\), the firing index. The Hebbian rule is then,

\[\begin{aligned}
\frac{d w_{ij}}{ dt} = S_{j}(t) \int^{\infty}_{0} \mathrm{d}s\: w_{+}(s) S_{i}(t - s ) +  S_{i}(t) \int^{\infty}_{0} \mathrm{d}s\: w_{-}(s) S_{j}(t - s ) \:.\end{aligned}\]
