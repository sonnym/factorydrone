<?php
Factory::define('', 'factory', array(
  'foo' => 'bar',
  'sequence' => Factory::sequence(function ($n) { return "sequence {$n}"; }),
));
