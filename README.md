# Sinusoidal Pulse Width Modulation

### Generate three phase AC signals through inductive loads

This program can be used as a driver for the following two-level inverter:<br/>
![The schematics of a two-level inverter with passive diode front-end, DC-link capacitor and a motor equivalent connected. Snubbers and anti-parallel diodes are not shown.](https://images.squarespace-cdn.com/content/v1/584729023e00bebf8abd6ba0/1495979634191-IJUTF9ERVVJDQNI2VXAB/image-asset.png?format=1000w)<br/>
Image from [switchcraft.org](https://www.switchcraft.org/)
<br/>
<br/>
To adjust the frequency of the fundamental waves, adjust the following:<br/>
<br/>
$`\text{TIM6}_{\text{Period}}=\frac{32\text{M}}{\text{Sine}_f \text{Q}_\text{Levels} \text{TIM6}_\text{Prescaler}}`$
<br/>
<br/>
The `lookup-gen` branch can be used to generate lookup tables for the three phases.
