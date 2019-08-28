#!/usr/bin/perl
use strict;
use warnings;

sub f_x {
    my $x = shift;
    return ($x ** 3.00) - (9.42478 * ($x ** 2.00)) + (29.60881 * $x) + 31.00628;
}

sub df_x {
    my $x = shift;

    return (3 * ($x ** 2)) - (2.00 * 9.42478 * $x) + 29.60881;
}


sub newton {
    my $x = shift;

    return $x - (f_x($x) / df_x($x));
}

my $x_n1 = 0;
my $prev = $x_n1;
while (1) {
    $x_n1 = newton($x_n1);
    if (sprintf("%.5f", $x_n1) eq sprintf("%.5f", $prev)) {
        last;
    }
    $prev = $x_n1;
}

print "$prev\n";

