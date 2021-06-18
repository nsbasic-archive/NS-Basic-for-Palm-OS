my %bits = 
(
	"*" => 32,
	"**" => 32,
	short => 16,
	long => 32,
	MemHandle => 32,
	VoidPtr => 32,
	VoidHand => 32,
	WChar => 16,
	UInt16 => 16,
	UInt32 => 32,
	Int16 => 16,
	double => 64,
	DmOpenRef => 32,
	MenuBarPtr => 32,
	WinHandle => 32,
);

my %args =
(
	SwapCodeBlock => "(struct codeBlock *pnoP)",
	SwapUserData => "(PNOBlock *pnoP)",
	SwapDataElem => "(struct dataelem *pnoP)",
);


my $swapOn = 0;


#Do the user data
open INFILE, "NSBPNOShared.h" or die;
&doit;
close INFILE;

#Do the stuff in copy.h
open INFILE, "copy.h" or die;
&doit;
close INFILE;


sub doit
{

while (<INFILE>)
{
    if ($swapOn)
    {
	if (/end swap/)
	{
	    $swapOn = 0;
print OUTFILE "
}
";
	    close OUTFILE;
	}
	else
	{
	    my $bits = 0;

	    chomp;
	    s/^\s+//;
	    s/;$//;
	    s/(\*+)/ \1 /;	    

	    my @words = split(/\s+/);
	    my $var = pop(@words);
	
	    foreach my $t (reverse @words)
	    {
		$bits = $bits{$t};
		warn "Bad type $t $bits" if !$bits;
		last if $bits;
	    }

	    if ($bits == 32 || $bits == 16)
	    {
	    print OUTFILE "    t$bits = (UInt$bits) (pnoP -> $var);\n";
	    print OUTFILE "    t$bits = ByteSwap$bits(t$bits);\n";
	    print OUTFILE "    pnoP -> $var = (" . join(' ', @words) . ") t$bits;\n";
	    }
	    elsif ($bits == 64)
	    {
		print OUTFILE "    d.d = pnoP -> $var;\n";
		print OUTFILE "    t32 = d.i.high;\n";
		print OUTFILE "    d.i.high = ByteSwap32(d.i.low);\n";
		print OUTFILE "    d.i.low = ByteSwap32(t32);\n";
		print OUTFILE "    pnoP -> $var = d.d;\n";
	    }
	    else
	    {
		warn "Bad value for bits: $bits";
	    }
	}
    }
    else
    {
	if (/begin swap (\w*)/)
	{
	    $swapOn = 1;
	    $funcName = $1;
print "begin swap $funcName\n";
	    my $args = $args{$funcName};
	    warn "No args for $funcName" if !$args;
		open OUTFILE, ">$funcName.c" or die;
	print OUTFILE "// Automatically generated from sud.pl

\#include \"PACEInterfaceLib.h\"
\#include \<PalmCompatibility.h\>
\#include \"copy.h\"
\#include \"NSBPNOShared.h\"
\#include \"NSBPNOGlue.h\"

void $funcName $args
{
    register UInt32 t32;
    register UInt16 t16;
    DoubleExchange d;

    if (!pnoP) return;

";
}

    }
}

}