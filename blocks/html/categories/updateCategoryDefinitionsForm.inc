<?php
/**
 * @copyright 2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Category $this->category
 */
$title = $this->category->getId() ? 'Edit Category Definitions' : 'Add Category';

$fields = array(
	'name', 'description', 'postingPermissionLevel', 'displayPermissionLevel',
	'categoryGroup_id', 'department_id'
);
foreach ($fields as $field) {
	$get = 'get'.ucfirst($field);
	$$field = isset($_POST[$field]) ? View::escape($_POST[$field]) : View::escape($this->category->$get());
}

$custom_fields = isset($_POST['custom_fields'])
	? View::escape($_POST['custom_fields'])
	: json_encode($this->category->getCustomFields());
?>

<script>
	$(function(){
		$('#my-form-builder').formbuilder({
			'save_url': '/categories/savedefinitions',
			'load_url': '/categories/getdefinitions?format=json&category_id=<?php echo $_REQUEST['category_id'];?>',
			'useJson' : true
		});
		$(function() {
			$("#my-form-builder ul").sortable({ opacity: 0.6, cursor: 'move'});
		});
	});
</script>

<h1><?php echo $title; ?></h1>
<form method="post" action="<?php echo BASE_URL; ?>/categories/update">
	<fieldset><legend>Category</legend>
		<input name="category_id" type="hidden" value="<?php echo $this->category->getId(); ?>" />
		
		<?php 

		
		echo "
		<h2>$name</h2>
		<p>$description</p>
		<table>
			<tr><th>Category Group</th>
				<td>$group</td>
			</tr>
			<tr><th>Default Department</th>
				<td>$department</td>
			</tr>
			<tr><th>Display Permission Level</th>
				<td>{$this->category->getDisplayPermissionLevel()}</td>
			</tr>
			<tr><th>Posting Permission Level</th>
				<td>{$this->category->getPostingPermissionLevel()}</td>
			</tr>
		</table>";
		?>

		<div id="my-form-builder"></div>
		<a class="cancel" href="<?php echo BASE_URL; ?>/categories">Cancel</a>
	</fieldset>
</form>
