<?php
/**
 * @copyright 2011-2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Category $this->category
 */
// Category customFields are Open311 attributes
// We adopted the Open311 standard for this feature
header("Content-Type: application/json");

$definition = array('id'=>$this->category->getId(), 'form_structure'=>$this->category->getCustomFields());

print json_encode($definition);



?>