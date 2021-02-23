
# Using DGML to understand PX4

As you may know I have a soft spot for Directed Graphs and I enjoy showing off what you can do with
[DGML diagrams and Visual Studio](https://lovettchris.github.io/posts/dgml_power_tools/).

I was recently struggling to debug a new problem that showed up in the [PX4 Firmware](https://github.com/PX4/Firmware)
with regards to Hardware in the loop (HITL) simulation and the [AirSim simulator](https://github.com/Microsoft/AirSim/).
Then I remembered I have this great tool...

See demo video:

[![thumb](/videos/PX4_topics.png)](https://lovettsoftwarestorage.blob.core.windows.net/videos/PX4_Topics.mp4)

Here's something fun for PX4 developers.  If you look in the modules/uORB folder you'll see the pub/sub infrastructure
called the "micro-orb" which is used for pub/sub messaging throughout the PX4 firmware.  But knowing where messages are coming
from and where they are going to can end up being quite a maze to figure out.  So if we search for every instance of ORB_ID
in the PX4 source code using this command:
```
grep -r . -e 'ORB_ID('
```
 you'll see lots of different uses.  You'll see `orb_publish` calls and you'll see `orb_subscribe` calls.
So if we capture all this output of this grep in a text file `orbids.txt` then we can process that file with my 
[graph_orbids.py](https://github.com/clovett/dgml/blob/master/tools/px4/graph_orbids.py) python script.

This script builds a graph of Nodes and Links which it can then save in a .dot or .dgml file format.
For the `orb_publish` calls it will create a node representing the module that is publishing with a link **to** another
node representing the orb topic.  For the `orb_subscribe` calls it will create a node  representing the module that is 
subscribing, with a link **from** another node representing the orb topic.

When you run the tool it will output anything it didn't understand, so check that output to make sure it didn't miss anything important.

Now you have a `graph.dgml` file which you can load up in Visual Studio.  You will see a large complex graph of all the pub/sub stuff
going on.  You can use the Legend to make the topic nodes green.
But the graph is pretty big an horrendous to look at which is kind of why its so hard to debug the PX4 until you fully understand this picture.

But if you install my [DgmlPowerTools](https://lovettchris.github.io/posts/dgml_power_tools/) extension for Visual Studio then you can slice and dice this graph a little more easily.  For example, I was investigating a problem with `actuator_outputs`.  So I can search for this topic, then select the Neighborhood Mode button in the toolbar to hide everything that is not 1 link away from this topic and you get this nice clean sub-graph:

![actuator_outputs](/posts/px4_topics/actuator_outputs.png).

This subgraph helped me fix the bug I was hunting.  I found that version 1.7
of the PX4 firmware contains the pwm_out_sim module, but version 1.8 does not.
Adding it back fixed my bug and HILT mode simulation works again in AirSim.

From here it's fun to pivot around the graph recentering each subgraph on a new module or topic.  For example, if you look a the `commander` 1 link away you see all the various topics the commander subscribes to, but you can see it is also publishing a bunch of stuff, like `vehicle_status`. 

![commander](/posts/px4_topics/commander.png)

You can recenter the graph on `vehicle_status` and see what it connects to:

![vehicle_status](/posts/px4_topics/vehicle_status.png)

From there you can see position control module (mc_pos_control) uses this, and you can easily pivot to see that node's local neighborhood:

![mc_pos_control](/posts/px4_topics/mc_pos_control.png)

The position controller subscribes to a bunch of things and produces one output which is used to move the drone.  Following that output we find that the land_detector uses this message as follows:

![landing_detector](/posts/px4_topics/landing_detector.png)

Who uses land_detected? Let's find out:

![land_detected.png](/posts/px4_topics/land_detected.png)

Interesting eh?  Here we see ekf2 which is the fancy new position estimator

![ekf2.png](/posts/px4_topics/ekf2.png)

And you can see from this picture that it is doing something pretty complicated fusing together lots of inputs to figure out where the drone is headed next.  One of the outputs is vehicle_attitude, which is an estimated attitude (or angle) of the drone.  Let's see who uses that:

![vehicle_attitude.png](/posts/px4_topics/vehicle_attitude.png)

Whoah, lots of people.  So you can see this is a handy way to slice and dice a complex graph.  In Visual Studio you can choose different layouts like 'left-to-right' and find what you like best.

Anyway, I found this useful so I hope you do too.






