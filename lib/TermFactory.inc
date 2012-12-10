<?php
/**
  * @file
  * Contains TermFactory.
  */

class TermFactory {
  /**
   * A method for creating taxonomy terms
   *
   * The term is created with the supplied options, persisted, and
   * returned to the caller.
   *
   * @param string $name
   *   The name of the factory to generate
   *
   * @param array $opts
   *   An associative array with options for the term
   *   - name: The name of the term.
   *
   * @return stdClass
   *   The new term
   *
   * @see http://api.drupal.org/api/drupal/modules%21taxonomy%21taxonomy.module/function/taxonomy_term_save/7
   */
  public static function create($name, $opts = array()) {
    $term = (object) array_merge(Factory::get_default_options($name), $opts);

    taxonomy_term_save($term);

    return $term;
  }
}
