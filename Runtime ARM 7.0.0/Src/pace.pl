my %size =
(
    UInt16 => 16,
    MemHandle => 32,
    DmOpenRef => 32,
    DmResID => 16,
    DmResType => 32
);

my %a0 =
(
    MemHandle => 1,
    DmOpenRef => 1,
);

my @functions = 
(
    "MemHandle   DmGetResource(DmResType type, DmResID ID)",
    "Err         DmReleaseResource(MemHandle rsrcH)",
    "UInt16 DmFindResource(DmOpenRef dbP, DmResType resType, DmResID resID, MemHandle resH)",
);

open HFILE, ">pace.h" or die;
open CFILE, ">pace.c" or die;

foreach my $func (@functions)
{
    if ($func =~ s/(\w+)\s*(\**)\s*//)
    {
	my ($type, $ptr) = ($1, $2);
	
	my $retSize = ($ptr) ? 32 : $size{$type};
	my $a0 = ($ptr) ? 1 : $a0{$type};

	$func =~ s/(\w*)//;
        my $funcName = $1;

		

	if ($func =~ s/[\(\)]//g)
	{
	    @args = split(/\s*,\s*/, $func);

	    my $tptr = join(" ", $type, $ptr);
	    $tptr=~ s/ *$//;
	    print HFILE "        $tptr", " " x (12 - length($tptr)), $funcName;
	    print HFILE "(", join(', ', @args) , ");\n";

	    print CFILE "PACE_CLASS_WRAPPER($tptr) $funcName(", join(', ', @args) , ")\n";
	    print CFILE "{
    PACE_PARAMS_INIT()\n";

	    foreach my $arg (@args)
	    {
		if ($arg =~ s/(\w+)\s*(\**)\s*//)
		{
	    	    my ($type, $ptr) = ($1, $2);
		    my $argSize = ($ptr) ? 32 : $size{$type};

		    if ($argSize)
		    {
			print CFILE "    PACE_PARAMS_ADD$argSize($arg)\n";
		    }
		    else
		    {
			warn "No size for type $type";
		    }
		}
		else
		{
		    warn "Bad arg $arg";
		}
	    }
	    if ($a0)
	    {
		print CFILE "    PACE_EXEC_RP(sysTrap$funcName, $tptr)\n";
	    }
	    else
	    {
		print CFILE "    PACE_EXEC(sysTrap$funcName, $tptr)\n";
	    }
	    print CFILE "}\n\n";
	}
	else
	{
	    warn "No parens in $func";
	}
    }
    else
    {
	warn "Bad declaration $func";
    }
}

close CFILE;
close HFILE;