<?php
/**
 * @copyright 2011-2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Category $this->category
 */
// Category customFields are Open311 attributes
// We adopted the Open311 standard for this feature
$attributes = array();
$customFields = $this->category->getCustomFields();
if ($customFields) {
	foreach ($customFields as $i=>$d) {
		$values = array();
		if (isset($d->values)) {
			foreach ($d->values as $value) {
				$values[] = array('key'=>$value,'name'=>$value);
			}
		}
		
		// reset the array
		$new_attributes = array();

		// this should be user provided, just faking it now			
		$new_attributes['variable'] 			= true;
		
		// this should be user provided, just faking it now
		$code_temp 								= (strlen($d->title)) ? $d->title : $d->values;
		$new_attributes['code'] 				= str_replace(' ', '-', strtolower($code_temp));
		
		// the order is actually set by the user, but it only comes in as the order of the array, not explicit values. Let's fix that
		$new_attributes['order'] 				= $i+1;
		
		// filter the names of form field types
		switch ($d->cssClass) {
			case 'select':
				if ($d->multiple == 'checked') {
					$new_attributes['datatype'] = 'multivaluelist';
					$new_attributes['datatype_description'] = 'Select an option';	
				} else {
					$new_attributes['datatype'] = 'singlevaluelist';						
					$new_attributes['datatype_description'] = 'Select one or more options';
				}
				break;
			case 'radio':
				$new_attributes['datatype'] = 'singlevaluelist';
				$new_attributes['datatype_description'] = 'Select an option';
				break;
			case 'checkbox':
				$new_attributes['datatype'] = 'multivaluelist';
				$new_attributes['datatype_description'] = 'Select one or more options';
				break;
			case 'input_text':
				$new_attributes['datatype'] = 'string';
				$new_attributes['datatype_description'] = 'Short text response';
				break;
			case 'textarea':
				$new_attributes['datatype'] = 'text';
				$new_attributes['datatype_description'] = 'Long text response';					
				break;					
		}
		
		// this should be user provided, just faking it now and drawing from datatype conventions set above
		//$new_attributes['datatype_description'] = '';	
									
		$new_attributes['required'] 			= ($d->required == 'checked') ? true : false;					
		$new_attributes['description'] 			= ($new_attributes['datatype'] == 'text' || $new_attributes['datatype'] == 'string') ? $d->values : $d->title;
		
		$option_values 							= $d->values;			
		$new_attributes['values'] 				= null;					
		
		
		if ($new_attributes['datatype'] !== 'text' && $new_attributes['datatype'] !== 'string') {
			foreach ($option_values as $option) {
			
				// should be user provided, just faking it now
				$key = null;
				$key = str_replace(' ', '-', strtolower($option->value));
			
				$new_attributes['values'][] = array('key' => $key, 'name' => $option->value);
				
			}		
		}
		
		$attributes[] = $new_attributes;



	}
}
header("Content-Type: application/json");
echo json_encode(array(
	'service_code' => (string)$this->category->getId(),
	'attributes'   => $attributes
));
