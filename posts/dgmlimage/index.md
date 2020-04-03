---
layout: page
title: DgmlImage
permalink: /posts/dgmlimage/
---

# DgmlImage

I'm happy to announce the availability of a new command line tool for generating images from DGML
graphs, called [DgmlImage](https://www.nuget.org/packages/DgmlImage/).

While [Visual Studio](https://visualstudio.microsoft.com/downloads/) provides excellent support for
viewing and editing DGML graphs, it is sometimes necessary to provide DGML graphs over the Web in
HTML pages as static images so that the value of DGML visualizations can be shared with the entire
world.

An excellent example of this is the [Reference Conflicts
Analyzer](https://marketplace.visualstudio.com/items?itemName=Dealogic.reference-conflicts-analyzer-azure-devops-task)
by József Kanczler.

In this example, you have a build server that runs code analysis tools, those tools provide insights
as DGML diagrams, and so then it is natural to want to visualize those results on a website for
anyone to see -- even folks who don't have Visual Studio handy.

`DgmlImage` is a standalone command line tool that can run on any Windows machine (including those
without Visual Studio).  The only pre-requisite is .NET Frameworks version 4.6.1.

## Install

To install this tool use "nuget install DgmlImage" like this:

```
d:\Temp>nuget install DgmlImage
Feeds used:
  https://api.nuget.org/v3/index.json
  C:\Program Files (x86)\Microsoft SDKs\NuGetPackages\

Installing package 'DgmlImage' to 'd:\Temp'.
  CACHE https://api.nuget.org/v3/registration5-gz-semver2/dgmlimage/index.json


Attempting to gather dependency information for package 'DgmlImage.1.2.0.1' with respect to project 'd:\Temp', targeting 'Any,Version=v0.0'
Gathering dependency information took 26.21 ms
Attempting to resolve dependencies for package 'DgmlImage.1.2.0.1' with DependencyBehavior 'Lowest'
Resolving dependency information took 0 ms
Resolving actions to install package 'DgmlImage.1.2.0.1'
Resolved actions to install package 'DgmlImage.1.2.0.1'
Retrieving package 'DgmlImage 1.2.0.1' from 'nuget.org'.
Adding package 'DgmlImage.1.2.0.1' to folder 'd:\Temp'
Added package 'DgmlImage.1.2.0.1' to folder 'd:\Temp'
Successfully installed 'DgmlImage 1.2.0.1' to d:\Temp
Executing nuget actions took 256.55 ms
```

Notice this has created a folder named `DgmlImage.1.2.0.1` in your current directory and in that
folder you will find the tool in the `tools` folder.  To make it easy to run this command the
command line you can edit your PATH environment accordingly:

```
set PATH=%PATH%;d:\Temp\DgmlImage.1.2.0.1\tools
```

## An example

command line might look like this:

```
DgmlImage test.dgml
```

This will produce a file in the same directory as the DGML document called "test.png".  You can
provide other file formats by providing the -format option.  One interesting image format for Web
pages is the SVG format:

```
DgmlImage -format svg test.dgml
```

Now you should see a test.svg file.  With SVG there is a fun trick you can do to make the diagram
automatically scale to fit the web browser window.  Open the .svg file in notepad and look for the
`width` and `height` properties.  You will find something like this:

```xml
<svg width="2031.10719130029" height="1662.5614805394789"
```

Then modify this using a `viewbox` as follows:

```xml
<svg viewbox="0,0,2031,1662" width="100%"
```

Now the diagram nicely stretches and shrinks as you resize the browser window.  You will need to
copy the `<svg>` element into an .html page to see this nice resizing behavior.  When you do that,
drop the XML declaration:

```
<?xml version="1.0" encoding="utf-8"?>
```

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
