# Genius in Simplicity

Someone recently asked me "what makes a good software architect"?
Good question.  There are, of course, many books on the subject but
these are the things that have helped me along the way:

1.  Write a huge amount of code.  Millions of lines.  This gives you a
    deep grounding in the issues faced by developers everywhere.  I
    have seen many “architects” get lost in the clouds, they lose
    perspective if they stop day to day writing code.

1.  Find teams that have the best software engineers on the planet and
    join those teams.  I’ve learned so much from working with amazing
    people like Erich Gamma, Anders Hejlsberg, Erik Meijer, Clemens
    Szyperski, Herman Venter, and many others.

1.  Learn every product you work on top to bottom, don’t live just in
    your own little corner of the product. I know that’s hard with
    some huge products.  But nothing is stopping you from learning the
    whole system top to bottom.  Use tools to help you understand how
    it works (logging, diagramming tools, debuggers).  Pretty soon you
    will find people coming to you to pick your brains.

One of my favorite saying is **“There is Genius in Simplicity”**.  Do
not be satisfied with a solution until you have gotten to the core
essence of the problem so you can deliver an elegantly simple
solution.  So very much software out there does not achieve this kind
of Simplicity and we all need to work much harder to achieve this.
Simplicity is not easy to achieve.

Have you noticed that a professor that really really knows their stuff
is able to make something really complex seem simple?  But a professor
who is new is not so good at explaining the same thing?  This is what
I mean by “genius of simplicity”.  The person who truly understands
the problem area deeply usually does the best job of coming up with a
“simple architecture” that “just works” and scales.

A perfect example of this is `git`.  Many source control systems
existed before `git`, but they all fell over due to complexity, they
contained bugs, data would go missing when you merged branches, or a
branch merge would take 12 hours, by which time there were conflicts
again, and so on, it was horrendous what we had to put up with. Linus
Torvalds was also fed up with other CVS systems and decided to write
his own, and he thought long and deeply about it and got to the core
essence of the problem, and built `git`. He didn't just architect it
and hand his grand plans over to a team of people.  He built it.

This is what I mean by “genius of simplicity”. Notice `git` is not a
trivial piece of software.  I'm not talking about "simplistic"
software. You don't achieve the “genius of simplicity” by cutting
features. Linus could have made `git` much simpler if it didn't
support branches. But of course then you'd have a simplistic toy.  I'm
talking about beautiful elegant design, those are the ones that
achieve true “genius of simplicity”.

Products that achieve this tend to have a very long life.  We all need
to do better at achieving this in our own products.  And we need to
push back on the tyranny of the urgent.  One time I was on a product
that made a terrible decision to ship something that cost the team 2
years of embarrassing bug fixing, simply because it would have taken 3
weeks to fix it before we shipped and that was "too much work" and
wouldn't fit the schedule according to the PM's at the time.  That's a
classic example of when the devs (including me) should have pushed
back harder.  This kind of professional integrity is required from a
software architect.  Sometimes the PM's will get quite upset with you
but over time they will start to notice your products seem to have a
much longer lifetime.

There's also a certain "completeness" to beautiful elegant design. Too
often we are tempted to cut critical features to meet a deadline and
we justify it by calling it the Minimum Viable Product (MVP). I say we
should instead be shooting for the Minimum Lovable Product (MLP) and
to achieve that you need a kind of functional completeness that
delights the customer.  When a customer hits a critical missing
feature they fall off a cliff of complexity trying to work around that
hole.  Any product that does this to a customer has completely missed
the target on “genius of simplicity”.  It is simplicity in the core
design of the product, and simplicity of "use" by customers. Both are
equally important.  Most PM's think simplicity of "use" by customers
is the only thing that is important.  I say you can't deliver that
without simplicity in the core design of the product.  At some point
the ugly monsters lurking in your code will rise up and bite the
customer.