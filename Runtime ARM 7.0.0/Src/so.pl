opendir DIR, '.';
@files = readdir(DIR);
closedir DIR;

foreach $file (@files)
{
    open IN, $file;
    while (<IN>)
    {
	chomp;
 	@lines = split(/\r/);
	foreach $line (@lines)
	{
	next if (! ($line =~ /char/));
	next if (! ($line =~ /\[([0-9]+)\]/));
        $n = $1;
  
  
        $big{$n} .= $file . ": " . $line . "\n";
        }
    }
    close IN;
}

foreach $key (reverse sort {$a <=> $b} keys %big)
{
    print $big{$key} . "\n";
}