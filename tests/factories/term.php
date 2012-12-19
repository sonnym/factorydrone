<?php
PhactoryDrone::define('term', 'term', array(
  'name' => PhactoryDrone::sequence(function ($n) { return "term_name{$n}"; }),
));
