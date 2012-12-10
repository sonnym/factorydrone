<?php
Factory::define('term', 'term', array(
  'name' => Factory::sequence(function ($n) { return "term_name{$n}"; }),
));
