<?php
/**
 * @file
 * Contains FactoryDrone.
 */

class FactoryDrone {
  /**
   * Paths from which to load factories
   */
  protected static $factoryPaths = array();

  /**
   * The factory definitions
   */
  protected static $definitions = array();

  /**
   * A method of registering factory definitions.
   *
   * A factory of type with name will be defined, allowing for calls to
   * FactoryDrone::create to simply look up and produce standard objects
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
   * A method for creating objects from factory definitions.
   *
   * The object is created with the supplied options, persisted,
   * and returned to the caller.
   *
   * @param string $name
   *   The name of the factory to generate
   *
   * @param array $opts
   *   An associative array with options for the factory
   *
   * @return object
   *   The newly created factory object
   */
  public static function create($name, $opts = array()) {
    $factory_object = (object) array_merge(FactoryDrone::getDefaultOptions($name), $opts);
    $factory_type = self::getType($name);

    switch ($factory_type) {
      case 'vocabulary':
        taxonomy_vocabulary_save($factory_object);
        break;

      case 'term':
        taxonomy_term_save($factory_object);
        break;

      case 'role':
        user_role_save($factory_object);
        break;

      case 'user':
        user_save($factory_object);
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
   * Returns the default options generated for a given factory.
   *
   * @param string $name
   *   The name of the factory options being fetched
   *
   * @return array
   *   The generated options
   */
  public static function getDefaultOptions($name) {
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
   * Returns the factory type for a given definition.
   *
   * @param string $name
   *   The name of the defintiion
   *
   * @return string
   *   The type of the factory
   */
  public static function getType($name) {
    return self::$definitions[$name]['type'];
  }

  /**
   * Creates a sequence to assist with uniqueness constraints.
   *
   * @param Closure $generator
   *   The method is passed a single numerical argument
   *   that increments on each call
   */
  public static function sequence(Closure $generator) {
    $accumulator = 0;

    return function () use ($generator, &$accumulator) {
      return $generator($accumulator++);
    };
  }

  /**
   * Adds a new search path for factories.
   *
   * @param string $path
   *   The path containing factory definitions
   */
  public static function addFactoryPath($path) {
    $realpath = realpath($path);

    if (!is_dir($realpath)) {
      throw new Exception('$path must be a directory.');
    }

    self::$factoryPaths[] = $realpath;
  }

  /**
   * This method loads and stores all factory definitions.
   */
  public static function loadDefinitions() {
    foreach (self::$factoryPaths as $path) {
      if ($handle = opendir($path)) {
        while (FALSE !== ($file = readdir($handle))) {
          if (drupal_substr($file, -4) == '.php') {
            require join(DIRECTORY_SEPARATOR, array($path, $file));
          }
        }
      }
    }
  }

  /**
   * A method for inspecting currently defined factories.
   *
   * @return array
   *   Array of factory definitions.
   */
  public static function getDefinitions() {
    return self::$definitions;
  }
}
