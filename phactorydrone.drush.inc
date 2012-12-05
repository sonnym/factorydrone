<?php
/**
 * @file
 * Drush integration for the phactorydrone module
 */

/**
 * Implments hook_drush_command().
 */
function phactorydrone_drush_command() {
  $items = array();

  $items['vocabulary-create'] = array(
    'description' => dt('Create and persist a taxonomy vocabulary.'),
    'arguments' => array(
      'name' => dt('The human-readable name of the vocabulary.'),
      'machine name' => dt('The machine name of the vocabulary.'),
      'hierarchy' => dt('The hierarchy level of the vocabulary.'),
    ),
    'required-arguments' => 3,
    'aliases' => array('fvc'),
  );

  $items['term-create'] = array(
    'description' => dt('Create and persist a taxonomy term.'),
    'arguments' => array(
      'vocabulary name' => dt('The machine name of the vocabulary in which to create the term'),
      'name' => dt('The name of the term.'),
    ),
    'required-arguments' => 2,
    'aliases' => array('ftc'),
  );

  return $items;
}

/**
 *  Command callback. Create a new taxonomy vocabulary
 */
function drush_phactorydrone_vocabulary_create($name, $machine_name, $hierarchy) {
  $opts = array('name' => $name,
                'machine_name' => $machine_name,
                'hierarchy' => $hierarchy,
               );

  $vocabulary = VocabularyFactory::create($opts);

  print "Created vocabulary with vid {$vocabulary->vid}.\n";
}

/**
 *  Command callback. Create a new taxonomy term.
 */
function drush_phactorydrone_term_create($machine_name, $term) {
  $opts = array('name' => $term);

  $term = TermFactory::create($machine_name, $opts);
  
  print "Created term with tid {$term->tid}.\n";
}
