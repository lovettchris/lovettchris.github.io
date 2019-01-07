---
layout: home
title: DgmlImage
permalink: /posts/dgmlimage/
---

# DgmlImage

I'm happy to announce the availability of a new command line tool for generating images from DGML graphs, called [DgmlImage](https://www.nuget.org/packages/DgmlImage/).

While [Visual Studio](https://visualstudio.microsoft.com/downloads/) provides excellent support for viewing and editing DGML graphs,
it is sometimes necessary to provide DGML graphs over the Web in HTML pages as static images so that the value of DGML visualizations
can be shared with the entire world.

An excellent example of this is the [Reference Conflicts Analyzer](https://marketplace.visualstudio.com/items?itemName=Dealogic.reference-conflicts-analyzer-azure-devops-task) by József Kanczler.  

In this example, you have a build server that runs code analysis tools, those tools provide insights as DGML diagrams, and so then
it is natural to want to visualize those results on a website for anyone to see -- even folks who don't have Visual Studio handy.

DgmlImage is a standalone command line tool that can run on any Windows machine (including those without Visual Studio).  An example
command line might look like this:

```
DgmlImage test.dgml
```

This will produce a file in the same directory as the DGML document called "test.png".  You can provide other file formats by providing
the -format option.  One interesting image format for Web pages is the SVG format:

```
DgmlImage -format svg test.dgml
```

Now you should see a test.svg file.

### Usage:

Type "DgmlImage -?" to see this help page:

```
Usage: DgmlImage /format:png /zoom:level files...
Converts given DGML documents to given image format
Options:
    /format:name, supported formats are 'png', 'bmp', 'gif', 'tiff', 'jpg', 'xps', 'svg' (default png)
    /f:name, short hand for /format:name
    /zoom:level, default zoom is 1.
    /z:level, short hand for /zoom:level
    /width:n, width of the image (defaults to 100% of graph size)
    /legend, show the legend (default hidden)
    /out:directory, the directory in which to write the image files
```

