# Jabberwocky
<strong>atob:</strong><br>
This takes as input a text file and outputs a text file of bits where each ASCII character in the input file is replaced by the sequence of bits which represents its ASCII code. Each bit is represented by either the character '0' or the character '1'.

<strong>btoa:</strong><br>
This takes as input a text file of bits (where each bit is given by either the character '0' or the character '1') and outputs a sequence of ASCII characters. Here, each sequence of 8 bits is converted to a single ASCII character. The number of bits in the input file is a multiple of 8.

<strong>jabber:</strong><br>
This takes as input a text file of bits (where each bit is given by either the character '0' or the character '1') and outputs a text file of bits.

<strong>wocky:</strong><br>
This takes as input a text file of bits (where each bit is given by either the character '0' or the character '1') and outputs a text file of bits. This transformation will undo jabber.

Here is T.S. Eliot's poem <a href="hollow.txt">Hollow Men</a> in free form.
Test my program on the above poem.

    $ ./atob hollow.txt bit-hollow.txt
    $ ./jabber bit-hollow.txt zap-hollow.txt
    $ ./wocky zap-hollow.txt kapow-hollow.txt
    $ ./btoa kapow-hollow.txt out.txt
    $ diff hollow.txt out.txt
Here are some output files: <a href="bit-hollow.txt"></a>, <a href="zap-hollow.txt"></a>, <a href="kapow-hollow.txt"></a>, and <a href="out.txt"></a>.
