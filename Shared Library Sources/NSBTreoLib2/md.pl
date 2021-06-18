use strict;

open OUTFILE, ">ref.html" or die;

my $state = "";
my %entries = ();
my $curEntry = "";
my $mainDescription = "";
my $inTable = 0;

while (<>)
{
    chomp;

    if (/Entry:/)
    {
	s/Entry: *//;
	if ($_)
	{
	    $curEntry = $_;
	}
	else
	{
	    $state = "Entry";
	}
    }
    elsif (/Syntax:/)
    {
	$state = "Syntax";
    }
    elsif (/Introduction:/)
    {
	$state = "Introduction";
    }
    elsif (/Description:/)
    {
	$state = "Description";
    }
    elsif (/Errors:/)
    {
	$state = "Errors";
    }
    elsif (/Example:/)
    {
	$state = "Example";
    }
    elsif (/See:/)
    {
	$state = "See";
    }
    else
    {
	if ($state eq "Entry")
	{
	    $curEntry = $_;
	}
	elsif ($state eq "Syntax")
	{
	    $entries{$curEntry}{"Syntax"} .= $_ . "\n";
	}
	elsif ($state eq "See")
	{
	    $entries{$curEntry}{"See"} .= $_;
	}
	elsif ($state eq "Introduction")
	{
	    if (/^\s*$/)
	    {
		$mainDescription .= "\n";
	    }
	    else
	    {
		$mainDescription .= $_ . " ";
	    }
	}
	elsif ($state eq "Description")
	{
	    if (/^\s*$/)
	    {
		$entries{$curEntry}{"Description"} .= "\n";
	    }
	    else
	    {
		$entries{$curEntry}{"Description"} .= $_ . " ";
	    }
	}
	elsif ($state eq "Errors")
	{
	    if (/^\s*$/)
	    {
		$entries{$curEntry}{"Errors"} .= "\n";
	    }
	    else
	    {
		$entries{$curEntry}{"Errors"} .= $_ . " ";
	    }
	}
	elsif ($state eq "Example")
	{
	    $entries{$curEntry}{"Example"} .= $_ . "\n";
	}
    }
}

print OUTFILE '<html><head>
<meta HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">
<title>Tech Note 30: Using the NSBTreoLib Shared Library</title>
<link rel="stylesheet" href="/style2.css"></head>
<BODY TEXT="#000000" LINK="#0000ff" VLINK="#800080" BGCOLOR="#ffffff">

<TABLE CELLSPACING=0 BORDER=0 WIDTH=478>
<TR><TD WIDTH="22%" VALIGN="TOP">
<P><IMG SRC="images/BigIcon.GIF" WIDTH=86 HEIGHT=103></TD>
    <TD WIDTH="78%" VALIGN="TOP">
<B><FONT FACE="Helvetica" SIZE=5>
      <h2>Tech Note 30: Using the NSBTreoLib Shared Library</h2>
	  <h3>June 17, 2004<FONT FACE="Helvetica" SIZE=2>
	  </font></h3>
	  </FONT><FONT FACE="Helvetica" SIZE=2>
	  <h5>Copyright 2004 NS BASIC Corporation</h5>
	  </font></B></TD>
</TR>
</TABLE>
<HR>

<h2>Contents:</h2>
<pre>
    <a href="#intro">Introduction</a>
    <a href="#quickRef">Index and Quick Reference</a>
    <a href="#fullRef">Full Reference</a>
</pre>
';

my %givenEntries = ();
my $n = '0000';

foreach my $key (sort keys %entries)
{
    $givenEntries{$key} = ++$n;    
}

#Introduction section
print OUTFILE '<hr><a name="intro"><h2>Introduction:</h2>
';

    foreach my $desc (split(/\n/, $mainDescription))
    {
	$desc =~ s/&/&amp;/g;
	$desc =~ s/>/&gt;/g;
	$desc =~ s/</&lt;/g;
 	$desc =~ s/_([^_]*)_/\<i\>\1\<\/i\>/g;
	$desc =~ s/\@([^@]*)\@/\<code\>\1\<\/code\>/g;
	$desc =~ s/\%/<br>/g;
	$desc =~ s/\#/\&nbsp;/g;

	if ($desc =~ /\t/)
	{
	    print OUTFILE '<table border="0" cellspacing="0" cellpadding="0">' if !$inTable;
	    $inTable = 1;
	    print OUTFILE "<tr><td>" . 
		join("</td><td>&nbsp; &nbsp; &nbsp;", split(/\t/, $desc)) . 
		"</td></tr>\n";
	}
	else
	{
	    if ($inTable)
	    {
		print OUTFILE "</table>";
		$inTable = 0;
	    }
	    print OUTFILE "<p>$desc</p>\n";
	}
    }

# Quick reference section
print OUTFILE '<hr><a name="quickRef"><h2>Index and Quick Reference:</h2>
';

print OUTFILE '<table border="0" cellspacing="0" cellpadding="0">
';

foreach my $key (sort keys %entries)
{
    my ($name, $type) = split(/\~/, $key);
    my $syntax = $entries{$key}{"Syntax"};
    my $ge = $givenEntries{$key};

	$syntax =~ s/_(\w*)_/\<i\>\1\<\/i\>/g; 

   print OUTFILE "  <tr>\n";

    print OUTFILE "    <td>";
    if ($ge)
    {
	print OUTFILE "<a href='#" . $ge . "'> $name</a>";
    }
    else
    {
	warn "No entry for $key";
    }
    print OUTFILE "    </td>";
    print OUTFILE "    <td>&nbsp; &nbsp; &nbsp;$type</td>\n";
    print OUTFILE "    <td>&nbsp; &nbsp; &nbsp;<code>$syntax</code></td>\n";
    print OUTFILE "  </tr>\n";
}

print OUTFILE '</table>';

print OUTFILE '<hr><a><a name="fullRef"><h2>Full Reference:</h2>
';

foreach my $key (sort keys %entries)
{
    my ($name, $class) = split(/\~/, $key);
    my $anchor = $givenEntries{$key};

    print OUTFILE "<a name='$anchor'>\n";

    $name =~ s/&/&amp;/g;
    $name =~ s/>/&gt;/g;
    $name =~ s/</&lt;/g;
 
    print OUTFILE "<h3>$name</h3>\n";
#    print OUTFILE "<h4>$class</h4>\n" if $class;
 
    print OUTFILE "<p>";

    my $syn;

    foreach $syn (split(/\n/, $entries{$key}{"Syntax"}))
    {
	$syn =~ s/_(\w*)_/\<i\>\1\<\/i\>/g;
	print OUTFILE "<code>$syn</code><br>\n";
    }
    print OUTFILE "</p>";

    my $desc;

    my $inTable = 0;

    foreach $desc (split(/\n/, $entries{$key}{"Description"}))
    {
	$desc =~ s/&/&amp;/g;
	$desc =~ s/>/&gt;/g;
	$desc =~ s/</&lt;/g;
 	$desc =~ s/_([^_]*)_/\<i\>\1\<\/i\>/g;
	$desc =~ s/\@([^@]*)\@/\<code\>\1\<\/code\>/g;
	$desc =~ s/\%/<br>/g;
	$desc =~ s/\#/\&nbsp;/g;

	if ($desc =~ /\t/)
	{
	    print OUTFILE '<table border="0" cellspacing="0" cellpadding="0">' if !$inTable;
	    $inTable = 1;
	    print OUTFILE "<tr><td>" . 
		join("</td><td>&nbsp; &nbsp; &nbsp;", split(/\t/, $desc)) . 
		"</td></tr>\n";
	}
	else
	{
	    if ($inTable)
	    {
		print OUTFILE "</table>";
		$inTable = 0;
	    }
	    print OUTFILE "<p>$desc</p>\n";
	}
    }
    if ($inTable)
    {
	print OUTFILE "</table>";
	$inTable = 0;
    }

    if ($entries{$key}{"Errors"})
    {
	print OUTFILE "<h4>Errors:</h4>\n";
 
	$inTable = 0;

    foreach $desc (split(/\n/, $entries{$key}{"Errors"}))
    {
	$desc =~ s/&/&amp;/g;
	$desc =~ s/>/&gt;/g;
	$desc =~ s/</&lt;/g;
 	$desc =~ s/_([^_]*)_/\<i\>\1\<\/i\>/g;
	$desc =~ s/\@([^@]*)\@/\<code\>\1\<\/code\>/g;
	$desc =~ s/\%/<br>/g;
	$desc =~ s/\#/\&nbsp;/g;

	if ($desc =~ /\t/)
	{
	    print OUTFILE '<table border="0" cellspacing="0" cellpadding="0">' if !$inTable;
	    $inTable = 1;
	    print OUTFILE "<tr><td>" . 
		join("</td><td>&nbsp; &nbsp; &nbsp;", split(/\t/, $desc)) . 
		"</td></tr>\n";
	}
	else
	{
	    if ($inTable)
	    {
		print OUTFILE "</table>";
		$inTable = 0;
	    }
	    print OUTFILE "<p>$desc</p>\n";
	}
    }
    if ($inTable)
    {
	print OUTFILE "</table>";
	$inTable = 0;
    }
   }

    if ($entries{$key}{"Example"})
    {
	print OUTFILE "<h4>Example:</h4>\n";
	print OUTFILE "<tt>\n";
	foreach my $ent (split(/\n/, $entries{$key}{"Example"}))
	{
    $ent =~ s/&/&amp;/g;
    $ent =~ s/>/&gt;/g;
    $ent =~ s/</&lt;/g;
 	    $ent =~ s/ /\&nbsp;/g;

	    print OUTFILE "$ent<br>\n";
	}
	print OUTFILE "</tt>\n";
    }
    if ($entries{$key}{"See"})
    {
	my @outEntries = ();
	print OUTFILE "<h4>Also see:</h4>\n<p>";
	foreach my $entry (split(/,/, $entries{$key}{"See"}))
	{
	    $entry =~ s/^ +//;
	    $entry =~ s/ +$//;

	    my $ge = $givenEntries{$entry};
	    if ($ge)
	    {
		$entry =~ s/\~.*//;
		push(@outEntries, "<a href='#" . $ge . "'> $entry</a>");
	    }
	    else
	    {
		$entry =~ s/\~.*//;
		warn "No entry $entry within $key";
		push (@outEntries, $entry);
	    }
	}
	print OUTFILE join(', ', @outEntries);
	print OUTFILE "</p>\n";
    }
}

print OUTFILE "</body></html>\n";

close OUTFILE;