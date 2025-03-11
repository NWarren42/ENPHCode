# ENPH 372 -- Assignment 2

Written by: Noah Warren

## Question 1: Negative Heat Capacity in a Solar Body

### Part A

To show that for two particles with identical masses in a circular orbit, the total gravitational potential energy of the system is $-2$ times the total kinetic energy of the system. We consider these two particles, which each of mass $m$,  are in a coupled orbit due to gravitational attraction. The radius of its orbit is denoted $r$, and each follows a circular orbit around the center of mass of the system.

Now lets consider the kinetic energy of one of the particles so that we can find the form of our final answer $-2 \times U_k$.

$$
U_{k, 1} = \frac{mv^2}{2}
$$

Assuming that the particles have equal velocity, for the total system the potential energy is double that of one particle giving:

$$
U_{k} = mv^2
$$

Now we recall that gravitational potential energy between two particles is given by the following equation simplified since both masses are equal. Note that the factor of 2 appears in front of $r$ as we assume the particles are equidistant from the center of their orbit.

$$ U_{grav} = -\frac{G m_1 m_2}{2r} = -\frac{G m^2}{2r}$$

For orbiting masses, we know that the only force present is the radial force that accelerates the particles towards each-other, coming in this case from gravity. If we then use Newton's second law we come up with the following formula.

$$
\frac{Gm^2}{(2r)^2} = ma
$$

Substituting the expression for radial acceleration, ($a_{rad} = v^2/r$) and doing some rearranging, we can construct something that looks like $U_k$.

$$
\begin{align}
\frac{Gm^2}{(2r)^2} &=m \frac{v^2}{r} \nonumber \newline
\frac{Gm^2}{(2r)} &=m \frac{v^2}{r} \times 2r \nonumber \newline
\frac{Gm^2}{2r} &= 2mv^2 \nonumber \newline
-\frac{Gm^2}{2r} &= -2mv^2 \nonumber \newline
U_{grav} &= -2 \times U_k \nonumber
\end{align}
$$

Subsequently proving that the gravitational potential energy of the system is $-2$ times the total kinetic energy of the system.

### Part B

To answer what happens if we add energy to this system lets consider the total kinetic energy of the system.

$$
U_{tot} =U_k + U_{grav} = U_k - 2U_k = -U_k
$$

This shows that if any energy is added to the system, the kinetic energy will decrease by the amount of energy added. Since $U_{grav} = -2 U_k$, we know then that gravitational potential energy will increase by $2$ times the amount added. To directly answer the question, if we add energy to the system, the average total kinetic energy will decrease.

### Part C

If we model the energy of a particle that makes up a star as:

$$
\bar U_k = \frac{3}{2} k \bar T
$$

Considering that we determined an expression for the total energy of a system like this in Part C, a star with $N$ particles then, the energy of the whole star is given by:

$$
U_{tot} = -\bar U_k = -N \frac{3}{2} k \bar T
$$

Knowing that heat capacity is defined as the derivative of energy with respects to temperature, we can then determine the heat capacity of the star.

$$
\frac{dU_{tot}}{dt} = -N \frac{3}{2} k
$$

We see that the heat capacity is in fact negative, which means that as more energy is added, the temperature of the star decreases. For a star, this could mean that as it radiates energy in the form of light, it heats up due to additional compression from gravity.

### Part D

First lets assume that G, M, and R are required components when dealing with the potential energy of a star. The dimensions of each of these values are given below.

$$
\begin{align}
[G] &= \frac{[N]L^2}{M^2} = \frac{ML}{T^2} \frac{L^2}{M^2} = \frac{L^3}{T^2M} \nonumber \newline
[M] &= M \nonumber \newline
[R] &= L \nonumber
\end{align}
$$

Noting that the dimension of energy is $[E] = [N]L = \frac{ML^2}{T^2}$, the only way to construct this dimensional equation is to multiply $[G]$ by $M^2$ and divide it by $[L]$:

$$
\frac{[G][M]^2}{[R]} = \frac{L^3}{T^2M} M^2 \frac{1}{L} = \frac{ML^2}{T^2} = [E]
$$

### Part E

To estimate the mass of the sun lets start with the values given to us.

$$
\begin{align}
m_{sun} &= 2 \times 10^{30}kg \nonumber \newline
r_{sun} &= 7 \times 10^{8} m \nonumber \newline
\end{align}
$$

Now we take the result of the virial theorem and expand it with the determined expressions for kinetic and potential energy.

$$
\begin{align}
U_{pot} &= -2U_k \nonumber \newline
-\frac{Gm_{sun}^2}{r_{sun}} &= -2 \times \frac{3}{2} NkT \nonumber \newline
T &= \frac{G m_{sun}^2}{3 r_{sun} N k} \nonumber \newline
\end{align}
$$

The number of particles in the sun is difficult to estimate, however if we take $m_{sun}/N$ as the average mass per particle, we can make the approximation that in the low atomic number particles found in the sun, the number of protons, neutrons, and electrons is roughly the same. Since $m_e << m_ p$, we can say that $\frac{m}{N} \approx \frac{2}{3} m_p$. Substituting into our above equation now, we know all the relevant quantities and can compute the average temperature of the sun.

$$
\begin{align}
T &= \frac{G m_{sun}}{3 r_{sun}k} \times \frac{2}{3} m_p \nonumber \newline
&= \frac{(6.67 \times 10^{-11} \frac{Nm^2}{kg^2})(2 \times 10^{30} kg) (\frac{2}{3} 1.67 \times 10^{-27} kg)}{3(7 \times 10^8 m)(1.38 \times 10^{-23} \frac{J}{K})} \nonumber \newline
&= 5.12 \times 10^6 K \nonumber \newline
\end{align}
$$

According to [NASA](https://science.nasa.gov/solar-system/temperatures-across-our-solar-system/#:~:text=The%20hottest%20part%20of%20the,F%20(5%2C500%C2%B0C).), the surface of the sun is a cool 5800K, whereas the core is about 15 000 000K. This puts our estimate within the agreed upon range of the sun's temperatures.

<div style="page-break-after: always;"></div>

## Question 2: Passing a Blind Taste Test

### Part A

If we assume that our friend has no ability at all between the different sources, but she knows there are 3 cups from each city, this means our friend will pick 3 cups from the 6 total that she believes are different. This is the exact definition of the binomial distribution 6 choose 3, and the multiplicity of this is represented as $\Omega = \binom{6}{3}$. Only one of these possibilities is correct however (she randomly chooses all 3 from one city), so the probability she guesses correctly is:

$$ P = \frac{1}{\Omega} = \frac{1}{\binom{6}{3}} = \frac{1}{20} = 0.05 $$

Giving us that the probability of our friend passing the test by chance is 5%.

### Part B

The way to reduce the probability of our friend guessing correctly is by increasing the number of glasses. Using the same expression as above (expanded now though to show the equation for $n$ choose $k$), if we let $n = 2k$, we solve for the minimum value of $k$ such that:

$$ \frac{1}{\binom{n}{k}} < 0.01 $$

Expanding and rearranging:

$$
\begin{align}
\frac{1}{\binom{2k}{k}} = \frac{k!(2k - k)!}{(2k)!} &< 0.01 \nonumber \newline
\end{align}
$$

The simplest way to solve this inequality is punching in values of $k$ until the inequality is satisfied. I tried using stirling's approximation but it only holds for large $n$ and the scale here isn't big enough I don't think.

For $k=3$ the result was a 5% success rate, so the next logical test is at $k=4$. This yields a success rate of 1.43%, which is still too high. $k=5$ yields a success rate of 0.40%, so to ensure our friend has a no more than 1/100 chance of success, we must have 5 cups from each city.

<div style="page-break-after: always;"></div>

## Question 3: N-dipole Paramagnet

### Part A

Before starting to solve this question, we must acknowledge that to use Stirling’s approximation, we must assume that $N$ is a large enough number tha the approximation will hold. The goal is to come up with the following expression to represent the height of the peak of the system's multiplicity distribution.

$$
\Omega_{\max} = 2^N \sqrt{\frac{2}{\pi N}}
$$

Similar to the earlier question about water cups, for a system with \( N \) dipoles, the multiplicity function is given by:

$$
\begin{align}
\Omega(N_\uparrow) = \binom{N}{N_\uparrow} &= \frac{N!}{N_\uparrow!(N - N_\uparrow)!} \nonumber \newline
&= \frac{N!}{N_\uparrow!N_\downarrow!} \nonumber \newline
\end{align}
$$

If we now apply the knowledge that the peak multiplicity occurs at \( N_\uparrow = N_\downarrow = \frac{N}{2} \), then we can write:

$$
\Omega_{\max} = \frac{N!}{(\frac{N}{2})!}
$$

Now for applying Stirling's approximation, for large N it is defined as:

$$
N! \approx \sqrt{2\pi N} \left( \frac{N}{e} \right)^N.
$$

Substituting into the expression for the maximum of the multiplicity function we get:

$$
\begin{align}
\Omega_{\max} &= \frac{\sqrt{2\pi N} (N/e)^N}{\left[ \sqrt{2\pi (N/2)} (N/2e)^{N/2} \right]^2} \nonumber \newline
&= \frac{\sqrt{2\pi N} (N/e)^N}{2\pi (N/2) (N/2e)^N} \nonumber \newline
&= \frac{(N/e)^N}{(N/2e)^N} \times \frac{\sqrt{2\pi N}}{2\pi (N/2)} \nonumber \newline
&= 2^N \times \frac{1}{\sqrt{\pi N / 2}} \nonumber \newline
&= 2^N \sqrt{\frac{2}{\pi N}} \nonumber \newline
\end{align}
$$

Which satisfies our original expression that was expected.

### Part B

Like in Part A, we are given a target expression to recreate using Stirling's approximation.

$$
\Omega = \frac{N!}{N_\uparrow! N_\downarrow!} \approx \frac{N^N}{N_\uparrow^{N_\uparrow} N_\downarrow^{N_\downarrow}} \sqrt{\frac{N}{2\pi N_\uparrow N_\downarrow}}
$$

Starting with out multiplicity function as determined earlier, we simply substitute Stirling’s approximation for large \( N \) when computing $N!$:

$$
\begin{align}
\Omega &= \frac{N!}{N_\uparrow! N_\downarrow!} \nonumber \newline
&\approx \frac{\sqrt{2\pi N} (N/e)^N}{\left[ \sqrt{2\pi N_\uparrow} (N_\uparrow/e)^{N_\uparrow} \right] \left[ \sqrt{2\pi N_\downarrow} (N_\downarrow/e)^{N_\downarrow} \right]} \nonumber \newline
\end{align}
$$

Splitting out our terms into fractions that are easier to deal with we get:

$$
\Omega \approx \frac{(N/e)^N}{(N_\uparrow/e)^{N_\uparrow} (N_\downarrow/e)^{N_\downarrow}} \times \frac{\sqrt{2\pi N}}{\sqrt{2\pi N_\uparrow} \sqrt{2\pi N_\downarrow}}.
$$

For the left-hand fraction, we recognize that $e^{N_\uparrow} \times e^{N_\uparrow} = e^{N_\uparrow + N_\downarrow} = e^N$, which cancels with the $e^n$ in the numerator leaving the left hand term as:

$$
\frac{N^N}{N_\uparrow^{N_\uparrow}N_\downarrow^{N_\downarrow}}
$$

Dealing with the right hand term, lets write it as:

$$
\frac{\sqrt{2 \pi} \sqrt{N}}{(\sqrt{2 \pi})^2 \sqrt{N_\uparrow N_\downarrow}}
$$

From which we see that the right hand fraction simplifies to:

$$
\sqrt{\frac{N}{2 \pi N_\uparrow N_\downarrow}}
$$

Which leaves our final equation for the multiplicity function as:

$$
\Omega \approx \frac{N^N}{N_\uparrow^{N_\uparrow} N_\downarrow^{N_\downarrow}} \sqrt{\frac{N}{2\pi N_\uparrow N_\downarrow}}
$$

Which is the target equation from the beginning.

### Part C

This question asks to derive an approximation for the multiplicity function near the peak where the following expressions for $N_{\uparrow}$ and $N_{\downarrow}$ hold.

$$
N_\uparrow = \frac{N}{2} + x, \quad N_\downarrow = \frac{N}{2} - x
$$

Let start by considering the multiplicity function that we derived earlier using Stirling's approximation.

$$
\Omega \approx \frac{N^N}{N_\uparrow^{N_\uparrow} N_\downarrow^{N_\downarrow}} \frac{1}{\sqrt{2\pi N_\uparrow N_\downarrow / N}}.
$$

This is a really ugly equation to work with so to simplify our exponents we take the logarithm of our multiplicity, the substitute the expressions for $N_\uparrow$ and $N_\downarrow$.

$$
\begin{align}
\ln \Omega &= N \ln N - N_\uparrow \ln N_\uparrow - N_\downarrow \ln N_\downarrow - \frac{1}{2} \ln (2\pi N_\uparrow N_\downarrow / N) \nonumber \newline
&= N \ln N - \left(\frac{N}{2} + x\right) \ln \left(\frac{N}{2} + x\right) - \left(\frac{N}{2} - x\right) \ln \left(\frac{N}{2} - x\right) - \frac{1}{2} \ln \left(2 \pi \left(\frac{N}{2} + x\right) \left(\frac{N}{2} - x\right) / N\right) \nonumber \newline
&= N \ln N - \left(\frac{N}{2} + x\right) \ln \left(\frac{N}{2} + x\right) - \left(\frac{N}{2} - x\right) \ln \left(\frac{N}{2} - x\right) - \frac{1}{2} \Bigg[ \ln (2\pi) + \ln \left(\frac{N}{2} + x\right) + \ln \left(\frac{N}{2} - x\right) - \ln N \Bigg] \nonumber
\end{align}
$$

If we assume that \( x \ll N \) because for a system with large $N$, the multiplicity function is so peaked that the system rarely ever fluctuates far from the peak of the multiplicity, i.e. $x$ is always $\ll N$. Because of this, we can use the taylor series expansion of a logarithm which tells us $ \ln (1+x) \approx x$. If first rearrange our logarithm terms for both $\frac{N}{2} + x$ and $\frac{N}{2} - x$, we end up with a form that lets us take advantage of this expansion. For the addition of x the calculation is shown below.

$$
\begin{align}
\ln \left( \frac{N}{2} + x \right) &= \ln \left(\frac{N}{2} \left(1 + \frac{2x}{N} \right)\right) \nonumber \newline
&= \ln \left( \frac{N}{2} \right) + \ln \left(1 + \frac{2x}{N} \right) \nonumber \newline
&\approx \ln \frac{N}{2} +  \frac{2x}{N} \nonumber
\end{align}
$$

Similarly for the subtracting term, the following can be proven.

$$
\ln \left( \frac{N}{2} - x \right) \approx \ln \frac{N}{2} - \frac{2x}{N}.
$$


If we now substitute these approximations into the logarithm of the multiplicity equation that we derived earlier we get the following massive equation.

$$
\begin{align}
\ln \Omega = N \ln N - \left( \frac{N}{2} + x \right) \left( \ln \frac{N}{2} + \frac{2x}{N} \right) &- \left( \frac{N}{2} - x \right) \left( \ln \frac{N}{2} - \frac{2x}{N} \right) - \frac{1}{2} \ln \left( 2\pi N/4 \right) \nonumber \\ 
&- \frac{1}{2} \Bigg[ \ln (2\pi) + \ln \frac{N}{2} + \xcancel{\frac{2x}{N}} + \ln \frac{N}{2} - \xcancel{\frac{2x}{N}} - \ln N \Bigg] \nonumber
\end{align}
$$

This equation is obviously huge so lets split it into two parts, the first two terms (excluding $N \ln N$) and the term in square brackets. Expanding the first term we get:

$$
\begin{align}
\left(\frac{N}{2} + x\right) \ln \frac{N}{2} + \left(\frac{N}{2} + x\right) \frac{2x}{N} &= \frac{N}{2} \ln \frac{N}{2} + x \ln \frac{N}{2} + \frac{2x}{N} \cdot \frac{N}{2} + \frac{2x^2}{N} \nonumber \newline
&= \frac{N}{2} \ln \frac{N}{2} + x \ln \frac{N}{2} + x + \frac{2x^2}{N} \nonumber
\end{align}
$$

Similarly for the second term...

$$
\begin{align}
\left(\frac{N}{2} - x\right) \ln \frac{N}{2} - \left(\frac{N}{2} - x\right) \frac{2x}{N} = \frac{N}{2} \ln \frac{N}{2} - x \ln \frac{N}{2} - x + \frac{2x^2}{N} \nonumber \newline
\end{align}
$$

And finally the term in square brackets:

$$
\frac{1}{2} \Big[ \ln (2\pi) + 2\ln \frac{N}{2} - \ln N \Big] = \frac{1}{2} \ln (2\pi) + \ln \frac{N}{2} - \frac{1}{2} \ln N
$$

All together then we get:

$$
\begin{align}
\ln \Omega &= N \ln N - \frac{N}{2} \ln \frac{N}{2} - \xcancel{x \ln \frac{N}{2}} - \cancel{x} - \frac{2x^2}{N} - \frac{N}{2} \ln \frac{N}{2} + \xcancel{x \ln \frac{N}{2}} + \xcancel{x} - \frac{2x^2}{N} \nonumber \\
&\quad - \frac{1}{2} \Bigg[ \ln (2\pi) + 2\ln \frac{N}{2} - \ln N \Bigg] \nonumber \\
&= N \ln N - N \ln \frac{N}{2} - \frac{4x^2}{N} - \frac{1}{2} \ln \left(\frac{\pi N}{2}\right) \nonumber
\end{align}
$$

Again we can expand a bit more using the identity $\ln \frac{N}{2} = \ln N - \ln 2$, which allows us to cancel our the $N \ln N$ terms and create the equation:

$$
\ln \Omega = N \ln 2 - \frac{4x^2}{N} - \frac{1}{2} \ln \left(\frac{\pi N}{2}\right)
$$

We're now in the home stretch and can now go raise everything to an exponent to recover our base multiplicity expression.

$$
\begin{align}
\Omega &= e^{N \ln 2} e^{-4x^2/N} e^{-\frac{1}{2} \ln (\pi N / 2)} \nonumber \newline
&= \frac{2^N}{\sqrt{\pi N / 2}} e^{-4x^2/N} \nonumber
\end{align}
$$

Which gives us an expression for the multiplicity function near its peak. Note that this function has an extra factor of 2 in the exponential term and I'm not sure where it came from in my math. The actual formula has a 2 instead of a 4, and is the formula we will use going forward.

### Part D

We aim to determine how wide the peak of the multiplicity function is by finding the value of \( x \) where:

$$
\frac{\Omega}{\Omega_{\max}} = e^{-1}
$$

We know that the multiplicity function near its peak follows a Gaussian who's form is shown above in part C, and we also found an expression for $\Omega _{max}$ in Part A. Now if we take \( \frac{\Omega}{\Omega_{\max}} \):

$$
\frac{\Omega}{\Omega_{\max}} = \frac{2^N}{\sqrt{\pi N / 2}} e^{-2x^2/N} \times \frac{1}{2^N \sqrt{\frac{2}{\pi N}}} = e^{-2x^2/N}
$$

By setting this result equal to \( e^{-1} \), we get an expression for $x$ as a function of $N$:

$$
\begin{align}
e^{-2x^2/N} &= e^{-1} \nonumber \\
\frac{2x^2}{N} &= 1 \nonumber \\
x &= \sqrt{\frac{N}{2}}
\end{align}
$$

Since this gives us an offset value from the peak, the full peak width is actually $2x$.
With this knowledge we now compute the width of our peak and compare it for different values of $N$.

First we calculate for $N = 10^4$.

$$
W = 2x = 2 \sqrt{\frac{10^4}{2}} = 2 \sqrt{5000} \approx 2 \times 70.7 \approx 141 \approx 1.4 \times 10^2
$$

We can see here that the width of our peak is two orders of magnitude smaller than the number of elements.

Similarly now for $N = 10^{22}$

$$
W = 2x = 2\sqrt{\frac{10^{22}}{2}} = 2\sqrt{5 \times 10^{21}} \approx 2 \times 7.07 \times 10^{10}.
$$

Again, we see that the width of the peak is way smaller than the number of particles, however this time it is closer to 12 orders of magnitude smaller. This shows that as $N$ increases, the ratio of width:particles gets increasingly smaller.

### Part E

This system is easily modelled as a binomial distribution for which we know as the number of particles increases, the width of the multiplicity peak becomes increasingly narrow. At 1 000 000 coins, I would think getting 501 000 heads and 499 000 tails would be pretty unlikely, however getting 510 000 heads would be way more unlikely. This is because the distribution is gaussian so as you get further away from the peak (in this case 500 000) the odds acheiving a specific state decrease drastically.

Using our information from part D, we can see roughly what falls within one standard deviation, or the width, of the peak.

$$
W = 2 \sqrt{\frac{10^{6}}{2}} \approx 1 400
$$

Which means that our standard deviation is roughly 700. With this knowledge, acheiving 1 000 more heads than expected isn't completely out of the question, however getting 10 000 more is extremely unlikely as we are now looking for a result two orders of magnitude greater than our standard deviation.

<div style="page-break-after: always;"></div>

## Question 4: Multiplicity of a 2D Ideal Gas

For this question we consider a gas confined to only be able to move in two dimensions and therefore occupies an area, and not a volume as we expect in a full 3D space.

Lets start by considering a single monatomic gas that is confined to our area. Intuitively, we can say that a region with twice the area would provide twice as many possible states for the atom to occupy, giving us the relationship $\Omega \propto A$. For a 2D plane, we also know that there are two possible momentum vectors that can contribute to the kinetic energy of the particle, denoted here as $p_x$ and $p_y$. These can give us a relationship for the kinetic energy of our particle:

$$
U = \frac{1}{2m} (p_x^2 + p_y^2)
$$

Which can alternatively be represented as:

$$
p_x^2 + p_y^2 = 2mU
$$

Which we can recognize as the equation of a circle in momentum space with radius $\sqrt{2mU}$. This then lets us talk about our area that the momentum vector for the particle can occupy in momentum space which is simply given by the circumference of the circle. This is because all possible momentum states are contained on this circle with radius R. This means our momentum "area" is given by $A_p = 2 \pi R = 2 \pi \sqrt{2mU}$.

The next step of this process is to count the number of microstates for the ideal gas. To do this consider the heisenberg uncertainty principle which is given by:

$$
\Delta x \Delta p_x \approx h
$$

This holds for each vector in a normal basis, which in this case the only other one is $y, P_y$. Consider now that the number of possible states for any of the quantities in position space is therefore $L/\Delta X$ and for momentum, $L_p / \Delta P_x$. In a two state system, the number of total allowed states is simply the product of the multiplicities of each individual component so the total multiplicity of this system is then:

$$
\frac{L L_p}{\Delta x \Delta P_x} = \frac{L L_p}{h} = \Omega _x
$$

This expression is of course only considering the x-direction, but this rule of multiplying multiplicities still holds if we want to move to two-dimensions. If we simply consider that $\Omega _y$ must have the same form as $\Omega _x$, we can write the following.

$$
\Omega _{xy} = \Omega _x \Omega _y = \frac{L_x L_y}{h} \frac{L_{px} L_{py}}{h} = \frac{A A_p}{h^2}
$$

Rearranging for $A_p$ and punching it back into the earlier formula which encapsulated all possible momentum states, we can come up with an expression for the total multiplicity of this 2D system.

$$
\Omega _{tot} = \frac{A}{h^2} 2 \pi \sqrt{2mU}
$$

This is for just one atom, so now lets generalize for the case of $N$ particles in which case we sum all the particles' momentums together to come up with a value for the total energy of the system.

This sum can be represented as:

$$
\sum{n}^{N} (P_{nx}^2 + P_{ny}^2) = 2mU_{tot}
$$

Now to look directly at our possible states, we have to include a factor of $1/N!$ to accommodate the fact that our particles are indistinguishable from one another. We also need to handle the fact that $A_p$ now takes on $2$ additional dimensions for each particle added, so we have to come up with a general form. This $N$ dimensional hyper-circle can be represented as:

$$
A_p = \frac{(2 \pi)^N}{({2N}/2 -1)!} r^{{2N}-1}
$$

With $r = \sqrt{2mU}$ Which we can sub into the equation for $\Omega _{xy}$ for:

$$
\Omega _{xy} = \frac{1}{N!} \frac{A^N}{h^{2N}} \frac{(2 \pi)^N}{(N - 1)!} \sqrt{2mU}^{{2N}-1}
$$

which we can then simplify to find:

$$
\Omega _N = \frac{(2 \pi m U A)^N}{(N!)^2 h^{2N}}
$$

Which gives us the relationship for multiplicity of our gas confined to 2D space.

<div style="page-break-after: always;"></div>

## Question 5

### Part A

We want to prove through dimensional analysis that the radius of a black hole should have a radius with on the order of:

$$
R = \frac{GM}{c^2}.
$$

Where $G$ is the gravitational constant, $M$ it the mass of the black hole, and $c$ is the speed of light, with their dimensions shown below.

$$
\begin{align}
[G] &= \frac{[N]L^2}{M^2} = \frac{ML}{T^2} \frac{L^2}{M^2} = \frac{L^3}{T^2M} \nonumber \newline
[M] &= M \nonumber \newline
[c^2] &= \frac{L^2}{T^2} \nonumber
\end{align}
$$

If we assume that this radius is purely a function of $G$, $M$, and $c$, we know the radius will have a dimension of $L$. To create an expression for the radius' dimension then, we need to cancel two factors of $L$ from the numerator of $G$, and eliminate all dimensions in the denominator.

The only way to do this is with the expression:

$$
[R] = \frac{[G][M]}{[c^2]} = \frac{L^3}{T^2 M} \times M \times \frac{T^2}{L^2} = L
$$

To compute an approximate radius of a black hole with the mass of our sun, we simply substitute the given values into this expression.

$$
\begin{align}
R &= \frac{(6.67 \times 10^{-11} \text{Nm}^2/\text{kg}^2) (2 \times 10^{30} \text{kg})}{(3 \times 10^8 \text{m/s})^2} \nonumber \\
&= 1482 \text{m} \nonumber
\end{align}
$$

Giving the black hole a radius on the order of kilometers!

### Part B

Starting off with what we know as the fundamental equivalence of mass and energy, we can build a model to calculate the total number of potential low-energy particles in a given black hole.

$$
E = M c^2.
$$

If we are assuming that black hole is made of low-energy photons, we can estimate the maximum number of photons that could be contained in it by considering the smallest amount of energy these photons could have. Since $E_{photon} \propto 1/\lambda$, the lowest possible energy state of a photon comes when $\lambda = R$ for the black hole, as any longer wavelengths of light wouldn't be able to be contained within it.

The individual energy for a photon of this wavelength can be calculated them to be:

$$
\begin{align}
E_{photon} &= \frac{hc}{\lambda} \nonumber \newline
&= \frac{hc}{R} \nonumber \newline
&= \frac{hc}{(GM/c^2)} = \frac{hc^3}{GM} \nonumber \newline
\end{align}
$$

Where we substitute the expression found in part A for the radius of the black hole.

Assuming that all the particles in the black hole then have this calculated energy as their sole form of energy, we know that the number of particles is simply the total energy divided by energy of each photon.

$$
N = \frac{E_{\text{total}}}{E_{\gamma}}.
$$

And since we've already established the relationship between energy and mass we can substitue this in for $E_{total}$ and solve for $N$.

$$
\begin{align}
N &= \frac{E_{\text{total}}}{E_{\gamma}} \nonumber \newline
&= \frac{G M^2}{h c} \nonumber
\end{align}
$$

If we now compare this to the given equation for entropy of large systems, we see that it will agree with the known formula for the entropy of a black hole.

$$
\begin{align}
S &\approx kN \nonumber \\
&= k \times \frac{G M^2}{h c} \approx \frac{8 \pi^2 G M^2}{h c} k \nonumber
\end{align}
$$

### Part C

To calculate the entropy of a one solar mass black hole we can use the definition given in Part B.

$$
\begin{align}
S_{b.h.} &= \frac{8 \pi^2 G M^2}{h c} k \nonumber \\
&= \frac{8 \pi^2 G (2 \times 10^{30})^2}{h c} k \nonumber \\
&= 1.46 \times 10^{54}
\end{align}
$$

For the sun, we consider that the particle mass is made up of almost entirely protons (or neutrons which have equivalent mass) which lets us calculate the number of particles ($N$) in the sun.

$$
\begin{align}
N_{sun} &= M_{sun}/m_p \nonumber \\
&= 2 \times 10^{30} / m_p \nonumber \\
&= 1.20 \times 10 ^{57} \nonumber \\
\end{align}
$$

If we now consider the sun as simply a body with a large particle count, its entropy is given by $S = k N_{sun} = 1.65 \times 10^{34} J$.

Comparing magnitudes now, if we take $S_{bh} / S_s$, we get that a black hole has around $10^{19}$ times more entropy than our sun for the same mass!
