<?php
PhactoryDrone::define('', 'factory', array(
  'foo' => 'bar',
  'sequence' => PhactoryDrone::sequence(function ($n) { return "sequence {$n}"; }),
));
