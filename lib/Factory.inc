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
   * @param array $opts
   *   An array containing the default options for the factory
   */
  public static function define($type, $name, $opts) {
    self::$definitions[$name] = array('type' => $type, 'opts' => $opts);
  }

  /**
   * A method for creating objects from factory definitions
   *
   * The object is created with the supplied options, persisted, and returned to the caller.
   *
   * @param string $name
   *   The name of the factory to generate
   *
   * @param array $opts
   *   An associative array with options for the node
   *
   * @return stdClass
   *   The new content type
   */
  public static function create($name, $opts = array()) {
    $factory_object = (object) array_merge(Factory::get_default_options($name), $opts);
    $factory_type = self::$definitions[$name]['type'];

    switch ($factory_type) {
      case 'vocabulary':
        taxonomy_vocabulary_save($factory_object);
        break;
      case 'term':
        taxonomy_term_save($factory_object);
        break;
      case 'content type':
        node_type_save($factory_object);
        break;
      case 'node':
        node_save($factory_object);
        break;
      default:
        throw new Exception("Factories of type '{$factory_type}' are not supported.");
    }

    return $factory_object;
  }

  /**
   * Returns the default options generated for a given factory
   *
   * @param string name
   *   The name of the factory options being fetched
   *
   * @return array
   *   The generated options
   */
  public  static function get_default_options($name) {
    if (!isset(self::$definitions[$name])) {
      throw new Exception("There is no factory definition called {$name}.");
    }

    $default_options = self::$definitions[$name]['opts'];

    foreach ($default_options as $name => $opt) {
      if (is_callable($opt)) {
        $default_options[$name] = $opt();
      }
    }

    return $default_options;
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
