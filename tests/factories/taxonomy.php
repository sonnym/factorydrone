<?php
Factory::define('vocabulary', 'vocab', array(
  'name' => Factory::sequence(function ($n) { return "taxonomy_name{$n}"; }),
  'machine_name' => Factory::sequence(function ($n) { "taxonomy_machine_name{$n}"; }),
  'heirarchy' => 0,
));
