
# WPF Animating Bar Chart

[![thumb](thumbnail.png)](https://youtu.be/RJA1Hk79Jbs)

So I found this really cool article by the famous Charles Petzold showing how to [Animate a Point
Collection](https://docs.microsoft.com/en-us/archive/msdn-magazine/2007/july/foundations-extending-the-wpf-animation-classes)
and it occurred to me that if you can animate a point collection then you can animate a bar chart
which is exactly what I was wanting to do for my [Money.Net
application](http://lovettsoftware.com/#posts/mymoney.net/).

Click the thumbnail above to see a [little video demo](https://youtu.be/RJA1Hk79Jbs) of the result.  I [published the code](https://github.com/clovett/tools/tree/master/WpfAnimatingBarChart) on github.

I'm pretty happy with the result, the animation is nice and smooth when
animating 20 separate bars and their labels.  I love how the PointCollectionAnimation handles the rotation transition.  The colors
also fade from the previous to the next color when switching data series
which adds a surprisingly nice touch.

Now if only I had a complete charting library built this way...