<?php
PhactoryDrone::define('vocabulary', 'vocab', array(
  'name' => PhactoryDrone::sequence(function ($n) { return "vocabulary_name{$n}"; }),
  'machine_name' => PhactoryDrone::sequence(function ($n) { return "vocabulary_machine_name{$n}"; }),
  'heirarchy' => 0,
));
