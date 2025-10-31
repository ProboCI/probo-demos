<?php

/**
 * Implements hook_preprocess_paragraph__usda_infographic_accordion().
 */
function nel_preprocess_paragraph__usda_infographic_accordion(&$variables) {

  // Add the class
  $variables['attributes']['class'][] = 'usa-accordion-item';
  $variables['attributes']['class'][] = 'usda-infographic-accordion';

  // Controls
  $controls = 'uswds-paragraph-' . $variables['paragraph']->id();
  $variables['controls'] = $controls;

  // Expand the marked accordion item
  $expanded = (!empty($variables['elements']['#usda_expand']));
  $variables['expanded'] = ($expanded) ? 'true' : 'false';

  // Mark the first accordion as expanded
  $variables['content']['field_paragraphs'][0]['#usda_expand'] = TRUE;
}
