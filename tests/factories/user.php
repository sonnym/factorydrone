<?php
FactoryDrone::define('user', 'user', array(
  'name' => FactoryDrone::sequence(function ($n) { return "name${n}"; }),
  'mail' => FactoryDrone::sequence(function ($n) { return "foo${n}@example.com"; }),
));
