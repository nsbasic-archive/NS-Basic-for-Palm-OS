
my @args = 
(
"        (aac.allArgs[0].dataElem)",
"_val    (aac.allArgs[0].val)",
"_occ1   (aac.allArgs[0].occ1)",
"_occ2   (aac.allArgs[0].occ2)",
"_occ3   (aac.allArgs[0].occ3)",
"_sde1   (aac.allArgs[0].sde1)",
"_sde2   (aac.allArgs[0].sde2)",
"_sde3   (aac.allArgs[0].sde3)",

);


for ($k = 1; $k <= 6; ++$k)
{
my $i = $k - 1;
print "#ifdef __MC68K__\n";

foreach $arg (@args)
{
    print "#define arg$k";
    my $arg2 = $arg;
    $arg2 =~ s/0/$i/;
    print "$arg2\n";
}
print "#endif

";
}