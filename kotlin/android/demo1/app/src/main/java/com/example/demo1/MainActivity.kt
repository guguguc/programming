package com.example.demo1

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView

class MainActivity : AppCompatActivity() {

    private lateinit var todoAdapter: TodoAdapter

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val rvTodoItemsView = findViewById<RecyclerView>(R.id.rvTodoItems)
        val btnAddTodo = findViewById<Button>(R.id.btnAddTodoItem)
        val etToDoTitle = findViewById<EditText>(R.id.etToDoTitle)
        val btnDeleteDown = findViewById<Button>(R.id.btnDeleteTodoItem)
        // empty list
        todoAdapter = TodoAdapter(mutableListOf())
        rvTodoItemsView.adapter = todoAdapter

        rvTodoItemsView.layoutManager = LinearLayoutManager(this)
        btnAddTodo.setOnClickListener{
            val todoTile = etToDoTitle.text.toString()
            if (todoTile.isNotEmpty()) {
                val todo = Todo(todoTile)
                todoAdapter.addTodo(todo)
                etToDoTitle.text.clear()
            }
        }
        btnDeleteDown.setOnClickListener {
            todoAdapter.deleteDoneTodos()
        }
    }
}