<?php
/**
 * @copyright 2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class CategoriesController extends Controller
{
	public function index()
	{
		$categoryList = new CategoryList();
		$categoryList->find();

		$this->template->setFilename('backend');
		$this->template->blocks[] = new Block(
			'categories/categoryList.inc',
			array('categoryList'=>$categoryList)
		);
	}

	public function view()
	{
		if ($this->template->outputFormat == 'html') {
			$this->template->setFilename('backend');
		}

		if (!empty($_REQUEST['category_id'])) {
			try {
				$category = new Category($_REQUEST['category_id']);
				$this->template->blocks[] = new Block('categories/info.inc', array('category'=>$category));
			}
			catch (Exception $e) {
				$_SESSION['errorMessages'][] = $e;
			}
		}
	}

	public function update()
	{
		// Load the $category for editing
		if (isset($_REQUEST['category_id']) && $_REQUEST['category_id']) {
			try {
				$category = new Category($_REQUEST['category_id']);
			}
			catch (Exception $e) {
				$_SESSION['errorMessages'][] = $e;
				header('Location: '.BASE_URL.'/categories');
				exit();
			}
		}
		else {
			$category = new Category();
		}


		if (isset($_POST['name'])) {
			try {
				$category->handleUpdate($_POST);
				$category->save();
				header('Location: '.BASE_URL.'/categories');
				exit();
			}
			catch (Exception $e) {
				$_SESSION['errorMessages'][] = $e;
			}
		}

		$this->template->setFilename('backend');
		$this->template->blocks[] = new Block('categories/updateCategoryForm.inc',array('category'=>$category));
	}
	
	
	public function definitions()
	{
		// Load the $category for editing
		if (isset($_REQUEST['category_id']) && $_REQUEST['category_id']) {
			try {
				$category = new Category($_REQUEST['category_id']);
			}
			catch (Exception $e) {
				$_SESSION['errorMessages'][] = $e;
				header('Location: '.BASE_URL.'/categories');
				exit();
			}
		}
		else {
			$category = new Category();
		}


		if (isset($_POST['name'])) {
			try {
				$category->handleUpdate($_POST);
				$category->save();
				header('Location: '.BASE_URL.'/categories');
				exit();
			}
			catch (Exception $e) {
				$_SESSION['errorMessages'][] = $e;
			}
		}

		$this->template->setFilename('backend');
		$this->template->blocks[] = new Block('categories/updateCategoryDefinitionsForm.inc',array('category'=>$category));
	}	
	
	
	public function getdefinitions()
	{
		
		// Return internal JSON format for service definition
			
		// Load the $category for editing
		if (isset($_REQUEST['category_id']) && $_REQUEST['category_id']) {
			try {
				$category = new Category($_REQUEST['category_id']);
			}
			catch (Exception $e) {
				$_SESSION['errorMessages'][] = $e;
				header('Location: '.BASE_URL.'/categories');
				exit();
			}
		}	
		
		$this->template->setFilename('definitionsjson');
		$this->template->blocks[] = new Block('categories/CategoryDefinitionsJSON.inc',array('category'=>$category));		
			
	}	
	
	
	public function savedefinitions()
	{
		
		// Return internal JSON format for service definition
			
		// Load the $category for editing
		if (isset($_REQUEST['category_id']) && $_REQUEST['category_id']) {
			try {
				$category = new Category($_REQUEST['category_id']);
			}
			catch (Exception $e) {
				$_SESSION['errorMessages'][] = $e;
				header('Location: '.BASE_URL.'/categories');
				exit();
			}
		}	
		
		if (isset($_REQUEST['frmb'])) {
			try {
				
				$form = $_REQUEST['frmb'];
								
				$category = new Category($_REQUEST['form_id']);				
				$category->setCustomFields(json_encode($_REQUEST['frmb']));
				
				//$category->handleUpdate($_POST);
				$category->save();
				echo 'success';
				//header('Location: '.BASE_URL.'/categories');
				exit();
			}
			catch (Exception $e) {
				$_SESSION['errorMessages'][] = $e;
			}
		}		
		
		
	}	
	
	
	

	/**
	 * Displays the list of all the categories
	 *
	 * Each category will be linked back to $return_url
	 */
	public function choose()
	{
		$return_url = !empty($_GET['return_url'])
			? new URL($_GET['return_url'])
			: new URL(BASE_URL.'/categories/view');

		$categoryList = new CategoryList();
		$categoryList->find(null,array('name'=>1));

		$this->template->blocks[] = new Block(
			'categories/categoryChoices.inc',
			array('categoryList'=>$categoryList,'return_url'=>$return_url)
		);
	}
}