#!/bin/bash

cat <<!
<!DOCTYPE html>

<meta charset="UTF-8">
<meta name="robots" content="index,follow" />
<meta http-equiv="refresh" content="60" />
<link rel=icon href="favicon.ico" sizes="any">

<style>
body { font-family: sans-serif; }
</style>

<title>LFT</title>

<h1>BUYS</h1>
<pre>
$(cat buys.csv)
</pre>

<h1>SELLS</h1>
<pre>
$(cat sells.csv)
</pre>
!
