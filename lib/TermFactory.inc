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
   * @param string $vocabulary_name
   *   The machine name of the vocabulary in which to create the term
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
  public static function create($vocabulary_name, $opts = array()) {
    // load taxonomy and prepare options
    $vocabulary = taxonomy_vocabulary_machine_name_load($vocabulary_name);
    $default_opts = array('vid' => $vocabulary->vid);

    // prepare and save new term
    $term = (object) array_merge($default_opts, $opts);
    taxonomy_term_save($term);

    return $term;
  }
}
