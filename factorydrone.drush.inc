<?php
/**
 * @file
 * Drush integration for the factorydrone module
 */

/**
 * Implments hook_drush_command().
 */
function factorydrone_drush_command() {
  $items = array();

  $items['factorydrone-create'] = array(
    'description' => dt('Create and persist a new factory object.'),
    'arguments' => array(
      'name' => dt('The name of the factory on which to base the new object.'),
      'key=value...' => dt('Any additional options you want to pass to the factory for overriding defaults.'),
    ),
    'options' => array(
      'porcelain' => dt('Print output in format intended for script consumption.'),
      'factory_path' => array(
        'description' => dt('Path to load factories from (multiple values allowed)'),
        'value' => 'required',
      ),
    ),
    'required-arguments' => 1,
    'aliases' => array('pd-create', 'pdc'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_DATABASE,
  );

  return $items;
}

/**
 *  Command callback. Create a new object
 */
function drush_factorydrone_create($name = NULL) {
  if ($factory_path = drush_get_option('factory_path')) {
    FactoryDrone::add_factory_path($factory_path);
    FactoryDrone::load_definitions();
  }

  $object = call_user_func_array('_drush_factorydrone_create', func_get_args());

  if (drush_get_option('porcelain')) {
    print serialize($object);
  } else {
    print "Created new object.\n";
    print_r($object);
    print "\n";
  }
}

/**
 * Function for creating an object
 *
 * @param string $name
 *   The name of the factory template to use
 *
 * @param string $options...
 *   (optional) Additional options to override the factory template, in the form key=value
 *
 * @return object
 *   The newly created object
 */
function _drush_factorydrone_create($name = NULL) {
  $args = func_get_args();
  $factory_options = array();

  if ($args) {
    $name = array_shift($args);
    
    foreach ($args as $arg) {
      list($key, $value) = explode('=', $arg);
      $factory_options[$key] = $value;
    }
  }

  return FactoryDrone::create($name, $factory_options);
}
