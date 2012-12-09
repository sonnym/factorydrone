<?php
/**
 * @file
 * Contains Factory.
 */

class Factory {
  /**
   * Paths from which to load factories
   */
  private static $factory_paths = array();

  /**
   * The factory definitions
   */
  private static $definitions = array();

  /** 
   * A method of registering factory definitions
   *
   * A factory of type with name will be defined, allowing for calls to
   * Factory::create to simply look up and produce standard objects
   *
   * @param string $type
   *   The type of the object to create, accepted values are:
   *   - taxonomy
   *   - term
   *
   * @param string $name
   *   The name to register for the factory (must be unique)
   *
   * @param Closure $opt_cb
   *   A callback used for generating default options of the factory
   */
  public static function define($type, $name, $opt_cb) {
    self::$definitions[$name] = array('type' => $type, 'opt_cb' => $opt_cb);
  }

  /**
   * Creates a sequence to assist with uniqueness constraints
   *
   * @param Closure $generator
   *   The methos is passed a single numerical argument that increments on each call
   */
  public static function sequence(Closure $generator) {
    $accumulator = 0;

    return function () use ($generator, &$accumulator) {
      return $generator($accumulator++);
    };
  }

  /**
   * Adds a new search path for factories
   *
   * @param string $path
   *   The path containing factory definitions
   */
  public static function add_factory_path($path) {
    $realpath = realpath($path);

    if (!is_dir($realpath)) {
      throw new Exception('$path must be a directory.');
    }

    self::$factory_paths[] = $realpath;
  }

  /**
   * This method loads and stores all factory definitions
   */
  public static function load_definitions() {
    foreach (self::$factory_paths as $path) {
      if ($handle = opendir($path)) {
        while (FALSE !== ($file = readdir($handle))) {
          if (substr($file, -4) == '.php') {
            require join(DIRECTORY_SEPARATOR, array($path, $file));
          }
        }
      }
    }
  }

  /**
   * A method for inspecting currently defined factories
   *
   * @return array
   *   Array of factory definitions.
   */
  public static function get_definitions() {
    return self::$definitions;
  }
}
