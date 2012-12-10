<?php
Factory::define('vocabulary', 'vocab', array(
  'name' => Factory::sequence(function ($n) { return "vocabulary_name{$n}"; }),
  'machine_name' => Factory::sequence(function ($n) { return "vocabulary_machine_name{$n}"; }),
  'heirarchy' => 0,
));
